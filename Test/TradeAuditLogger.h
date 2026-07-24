#pragma once

#include <boost\signals2.hpp>
#include <iostream>
#include <sstream>
#include "../Infrastructure/PriceEvent/IMarketEvents.h"

class IMarketEvents;

class TradeAuditLogger{
    boost::signals2::scoped_connection m_connection;
    void OnTradeExecution(const ns::TradeExecutedEvent& event);
public:
    explicit TradeAuditLogger(IMarketEvents& events);
};