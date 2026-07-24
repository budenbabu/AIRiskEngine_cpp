#pragma once

#include <boost\signals2.hpp>
#include "PortfolioUpdatedEvent.h"
#include "../PriceEvent/IMarketEvents.h"
#include "../../Application/WebSocket/IWebSocketHub.h"
#include "../../Common/IJsonSerializer.h"

class PortfolioBroadcaster{
    boost::signals2::scoped_connection m_connection;
    IJsonSerializer& m_serializer;
    IWebSocketHub& m_hub;
    void onPorfolisUpdate(const ns::PortfolioUpdatedEvent& event);
public:
    PortfolioBroadcaster(IMarketEvents& even,IWebSocketHub& hub,IJsonSerializer& serializer);
};