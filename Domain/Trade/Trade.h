#pragma once

#include <chrono>
#include <nlohmann/json.hpp>
#include "TradeSide.h"

namespace ns{
    struct Trade{
        std::uint64_t tradeId{};
        std::string symbol;
        TradeSize side;
        int quantity{};
        double price{};
        std::uint64_t timestamp;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Trade,tradeId,symbol,side,quantity,price,timestamp)
    };
}