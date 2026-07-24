#include "TradeAuditLogger.h"

void TradeAuditLogger::OnTradeExecution(const ns::TradeExecutedEvent &event)
{
    std::ostringstream oss;
    oss<<"======== Trade Executed =========\n"
        <<"Symbol: "<<event.trade.symbol<<'\n'
        <<"Side: "<<(event.trade.side==ns::TradeSize::BUY?"BUY":"SELL")<<'\n'
        <<"Qty: "<<event.trade.quantity<<'\n'
        <<"Price: "<<event.trade.price<<'\n'
        <<"Position Qty: "<<event.position.quantity<<'\n'
        <<"Position Avg Price: "<<event.position.averagePrice<<'\n'
        <<"=========================================\n";    
    std::cout<<oss.str();
}

TradeAuditLogger::TradeAuditLogger(IMarketEvents &events)
{
    std::cout << "TradeAuditLogger created\n";
    m_connection=events.SubscribeTradeExecuted([this](const ns::TradeExecutedEvent& event){
        OnTradeExecution(event);
    });
}
