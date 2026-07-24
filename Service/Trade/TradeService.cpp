#include "TradeService.h"





// bool TradeService::Buy(const ns::Trade &trade)
// {    
    // 
//    m_logger.Info(std::format("Repository address {}",static_cast<const void*>(&m_prepositiry)));
    // try{
        // auto conn=m_db.Acquire();
        // pqxx::work tx(*conn);
        // ns::Position finalPosition;
        // auto position=m_prepositiry.GetBySymbolForUpdate(tx,trade.symbol);    
        // if(!position){
            // finalPosition.symbol=trade.symbol;
            // finalPosition.averagePrice=trade.price;
            // finalPosition.marketPrice=trade.price;
            // finalPosition.quantity=trade.quantity;           
        // }else{
            // finalPosition=*position;
            // const double total=finalPosition.quantity*finalPosition.averagePrice+trade.quantity*trade.price;
            // finalPosition.quantity+=trade.quantity;
            // if(finalPosition.quantity!=0) finalPosition.averagePrice=total/finalPosition.quantity;
        // }
        // m_prepositiry.Upsert(tx,finalPosition);                
        // m_trepositor.Add(tx,trade);
        // tx.commit();    
        // ns::TradeExecutedEvent event{
            // .trade=trade,
            // .position=finalPosition,        
            // .realizedPnl=0.0
        // };
        // m_marketEvent.PublishTradeExecuted(event);        
        // return true;    
    // }catch(const std::exception& ex){
        // m_logger.Error(std::format("TradeService::Buy Exception: {}",ex.what()));
        // return false;        
    // }
// }
// 
// bool TradeService::Sell(const ns::Trade &trade)
// {
    // try{
        // auto conn=m_db.Acquire();
        // pqxx::work tx(*conn);
        // auto position=m_prepositiry.GetBySymbolForUpdate(tx,trade.symbol);    
        // if(!position) return false;
        // auto updated=*position;
        // if(trade.quantity > updated.quantity) {        
            // return false;
        // }
        // double realized =(trade.price -updated.averagePrice)* trade.quantity;
        // updated.realizedPnl+=realized;
        // updated.quantity -= trade.quantity;
    // 
        // if(updated.quantity == 0){
            // m_prepositiry.Remove(tx,updated.symbol);
        // }
        // else{ 
            // m_prepositiry.Upsert(tx,updated);
        // }
// 
        // m_trepositor.Add(tx,trade);
        // tx.commit();
// 
        // ns::TradeExecutedEvent event{
            // .trade=trade,
            // .position=updated,        
            // .realizedPnl=realized
        // };
        // m_marketEvent.PublishTradeExecuted(event);    
        // return true;
    // }catch(const std::exception& ex){
        // m_logger.Error(std::format("TradeService::Sell Exception: {}",ex.what()));
        // return false;
    // }
// }

bool TradeService::Sell(const ns::Trade &trade, const std::optional<ns::Position> &postion, pqxx::transaction_base &tx)
{
    if(!postion){
        m_logger.Error("Postion not found");
        return false;
    }

    auto updated=*postion;
    if(trade.quantity > updated.quantity){
        m_logger.Error("Insufficient quantity");
        return false;
    }
    auto pnl=(trade.price-updated.averagePrice)*trade.quantity;
    updated.realizedPnl+=pnl;
    updated.quantity-=trade.quantity;
    updated.marketPrice=trade.price;
    if(updated.quantity==0){
        updated.averagePrice=0.0;
        updated.marketPrice=0.0;
    }
    if(!m_trepositor.Add(tx,trade)) return false;
    return m_prepositiry.Upsert(tx,updated);    
}

bool TradeService::Buy(const ns::Trade &trade, const std::optional<ns::Position> &postion, pqxx::transaction_base &tx)
{
    ns::Position updated;
    if(postion){
        updated=*postion;
        auto totalQty=updated.quantity+trade.quantity;
        auto totalCost=updated.averagePrice*updated.quantity+trade.price*trade.quantity;
        updated.averagePrice=totalCost/totalQty;
        updated.marketPrice=trade.price;
        updated.quantity=totalQty;
    }else{
        updated=ns::Position{
            .symbol=trade.symbol,
            .quantity=trade.quantity,
            .averagePrice=trade.price,
            .marketPrice=trade.price,
            .realizedPnl=0.0
        };
    }
    if(!m_trepositor.Add(tx,trade)) return false;
    return m_prepositiry.Upsert(tx,updated);    
}

TradeService::TradeService(ITradeRepository &trepositor, IPortfolioRepository &prepositiry,IMarketEvents &marketEvent, 
    ILogger &logger, PostgreSqlConnectionPool &db, RiskEngine &engine, IRiskViolationRepository& violation,IJsonSerializer& serializer,IWebSocketHub& hub,IRiskAIQueue& aiQueue) : m_trepositor(trepositor),
    m_prepositiry(prepositiry), m_marketEvent(marketEvent), m_logger(logger), m_db(db), m_engine(engine),m_violation(violation),
    m_serializer(serializer),m_hub(hub),m_aiQueue(aiQueue) {}

bool TradeService::Execute(const ns::Trade &trade)
{
    if(trade.tradeId !=0){
        if(m_trepositor.Exists(trade.tradeId)){
            throw std::runtime_error(std::format("Trade {} already exists",trade.tradeId));
        }
    }

    try{
        auto conn=m_db.Acquire();
        pqxx::work tx(*conn);
        auto position=m_prepositiry.GetBySymbolForUpdate(tx,trade.symbol);
        auto riskResult=m_engine.Validate(trade,position);
        if(!riskResult.allowed){
            m_logger.Warning(riskResult.reason);
            if(auto vid=m_violation.Add({
                .id=0,
                .timestamp=trade.timestamp,
                .symbol = trade.symbol,
                .violation = riskResult.violation,
                .message=riskResult.reason,                
                .tradeJson=m_serializer.SerializeObject<ns::Trade>(trade)
                }); vid != 0) {
                   m_aiQueue.Enqueue(vid);                 
            }
            tx.abort();
            m_hub.Brodcast(m_serializer.SerializeObject<ns::RiskResult>(riskResult));
            throw std::runtime_error(std::format("{}",riskResult.reason));
        }
        //auto result=m_engine.Validate(trade,posi)
        bool result={false};
        switch(trade.side){
            case ns::TradeSize::BUY : {
                m_logger.Info("TradeSize::BUY");
                result=Buy(trade,position,tx);
                break;
                //return false;
            }
            case ns::TradeSize::SELL: {
                m_logger.Info("TradeSize::SELL");
                //return true;
                 result=Sell(trade,position,tx);
                 break;
            }
            default: result=false;
        }

        if(!result){
            tx.abort();
            return false;
        }
        tx.commit();
        return true;

    }catch(const std::exception& ex){
        auto str=std::format("{}",ex.what());
        m_logger.Error(str);
        throw std::runtime_error(str);
    }
}

std::vector<ns::Trade> TradeService::GetTrades() const
{    
    return m_trepositor.GetAll();
}

std::optional<ns::Trade> TradeService::GetTrade(std::uint64_t tradeId) const
{
    if(!m_trepositor.Exists(tradeId)){
        throw std::runtime_error(std::format("Trade id {} not foud",tradeId));
    }
    auto trade=m_trepositor.GetById(tradeId);
    return trade;
}

std::vector<ns::Trade> TradeService::GetSymbolBytrade(const std::string& symbol) const
{
    return m_trepositor.GetBySymbol(symbol);
}