#include "TradeBroadcaster.h"

void TradeBroadcaster::onTradeExecuted(const ns::TradeExecutedEvent &event)
{
    auto json=m_serializer.Serialize(event);
    m_hub.Brodcast(json);
}

TradeBroadcaster::TradeBroadcaster(IMarketEvents &event, IWebSocketHub &hub, IJsonSerializer &serializer):
    m_hub(hub),m_serializer(serializer)
{
    m_connection=event.SubscribeTradeExecuted([this](const ns::TradeExecutedEvent& e){
        onTradeExecuted(e);
    });
}
