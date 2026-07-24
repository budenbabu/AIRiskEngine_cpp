#pragma once

#include <boost\signals2.hpp>
#include "IWebSocketHub.h"
#include "../../Common/IJsonSerializer.h"
#include "../../Infrastructure/PriceEvent/IMarketEvents.h"



class WebSocketBroadcaster {
    IWebSocketHub& m_hub;
    IJsonSerializer& m_serializer;
    boost::signals2::scoped_connection m_connection;
    void onPrieUpdateed(const PriceUpdatedEvent& event);

public:
    WebSocketBroadcaster(IMarketEvents& event, IWebSocketHub& hub, IJsonSerializer& serializer);
};