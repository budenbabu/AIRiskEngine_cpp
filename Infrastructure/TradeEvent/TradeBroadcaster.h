#pragma once

#include <boost\signals2.hpp>

#include "TradeExecutedEvent.h"
#include "../../Application/WebSocket/IWebSocketHub.h"
#include "../../Common/IJsonSerializer.h"
#include "../PriceEvent/IMarketEvents.h"

class TradeBroadcaster{
    IWebSocketHub& m_hub;
    IJsonSerializer& m_serializer;

    boost::signals2::scoped_connection m_connection;
    void onTradeExecuted(const ns::TradeExecutedEvent& event);
public:
    TradeBroadcaster(IMarketEvents& even,IWebSocketHub& hub,IJsonSerializer& serializer);
};