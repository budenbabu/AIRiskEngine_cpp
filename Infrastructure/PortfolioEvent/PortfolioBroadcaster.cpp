#include "PortfolioBroadcaster.h"

void PortfolioBroadcaster::onPorfolisUpdate(const ns::PortfolioUpdatedEvent &event)
{
    auto json=m_serializer.Serialize(event);
    m_hub.Brodcast(json);
}

PortfolioBroadcaster::PortfolioBroadcaster(IMarketEvents &event, IWebSocketHub &hub, IJsonSerializer &serializer) :
     m_hub(hub), m_serializer(serializer)
{
    m_connection=event.SubscribePortfolioUpdated([this](const ns::PortfolioUpdatedEvent& event){
        onPorfolisUpdate(event);
    });
}
