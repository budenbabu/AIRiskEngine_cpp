#include "WebSocketBroadcaster.h"



void WebSocketBroadcaster::onPrieUpdateed(const PriceUpdatedEvent& event)
{
	const auto json = m_serializer.Serialize(event.quote);
	m_hub.Brodcast(json);
}

WebSocketBroadcaster::WebSocketBroadcaster(IMarketEvents& event, IWebSocketHub& hub, IJsonSerializer& serializer)
	:m_hub(hub), m_serializer(serializer)  {
	m_connection = event.SubscribePriceUpdate([this](const PriceUpdatedEvent& event) {
		onPrieUpdateed(event);
	});
}
