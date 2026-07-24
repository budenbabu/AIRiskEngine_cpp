#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace ns{
    struct Position{
        std::string symbol;
        int quantity{};
        double averagePrice{};
        double marketPrice{};
        double realizedPnl{};
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Position,symbol,quantity,averagePrice,marketPrice,realizedPnl)
    };
}