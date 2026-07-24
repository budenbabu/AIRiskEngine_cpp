#pragma once
#include <nlohmann\json.hpp>
#include <string>

namespace ns{
    struct PositionPnL{
        std::string symbol;
        double averagePrice{};
        double marketPrice{};
        std::int64_t quantity{};
        double unrealizedPnl{};
        double marketValue{};
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PositionPnL,symbol,averagePrice,marketPrice,quantity,unrealizedPnl,marketValue)
    };
}