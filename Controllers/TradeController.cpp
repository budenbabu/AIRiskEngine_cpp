#include "TradeController.h"


TradeController::TradeController(ILogger &logger, HttpResponseFactory &factor, IJsonSerializer &serialize,ITradeService& service)
    :m_factor(factor),m_serialize(serialize),m_logger(logger),m_service(service){}

void TradeController::ExecuteTrade(RequestContext &context)
{
    const auto& request=context.GetRequest();    
    auto trade=m_serialize.DeserializeObject<ns::Trade>(request.body());
    m_logger.Info(std::format("Executing trade: {} {} {}",trade.tradeId,trade.symbol,static_cast<int>(trade.side)));    
    
     if(!m_service.Execute(trade)){
         auto str=std::format("Error Executing trade: {} {}",trade.tradeId,trade.symbol);
         m_logger.Error(str);
         context.setResponse(m_factor.InterServerError(R"({"message":"Error Trade executed "})",request));                      
     }
    context.setResponse(m_factor.OK(R"({"message":"Trade executed successfully"})",request));                
}

void TradeController::GetTradeById(RequestContext &context)
{
    auto& request=context.GetRequest();
    auto value=context.GetrouteValue("id");
    
    if(!value){
        context.setResponse(m_factor.NotFound("route value not found)",request)); 
        return;                     
    }
    m_logger.Info(std::format("requested Trade id {}",*value));
    auto id=std::stoull(*value);
    auto trade=m_service.GetTrade(id);
    if(!trade){
        context.setResponse(m_factor.NotFound(std::format("Trade id {} not found",id),request)); 
        return;
    }
    context.setResponse(m_factor.OK(*trade,request));

}

void TradeController::GetTradeBySymbol(RequestContext &context)
{
    const auto& request=context.GetRequest();
    auto value=context.GetrouteValue("symbol");
    if(!value){
        context.setResponse(m_factor.NotFound(std::format("route path not found"),request)); 
        return;                     
    }
    auto trades=m_service.GetSymbolBytrade(*value);
    context.setResponse(m_factor.OK(trades,request));
}

void TradeController::GetTrades(RequestContext &context)
{
    const auto& request=context.GetRequest();
    auto trades=m_service.GetTrades();
    context.setResponse(m_factor.OK(trades,request));
}
