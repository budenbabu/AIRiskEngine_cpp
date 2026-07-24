#pragma once

#include <nlohmann/json.hpp>
#include "../../Domain/Trade/Trade.h"
#include "../../Models/Position.h"


namespace ns{
    struct TradeExecutedEvent{
        ns::Trade trade;
        ns::Position position;
        double realizedPnl{};
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TradeExecutedEvent,trade,position,realizedPnl)
    };
}