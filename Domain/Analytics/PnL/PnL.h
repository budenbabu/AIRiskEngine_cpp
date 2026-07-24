#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>

namespace ns{
    struct PnL{
        std::string symbol;
        double cost{};
        double marketValue{};
        double unrealizedPnl{};
        double returPrecentage{};
        double realizedPnl{};
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PnL,symbol,cost,marketValue,unrealizedPnl,returPrecentage,realizedPnl)
    };

    struct PnLSummary{
        double totalcost{};
        double totalmarketValue{};
        double totalunrealizedPnl{};
        double totalreturPrecentage{};
        double totalRealizedPnl{};
        std::vector<ns::PnL> positions;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PnLSummary,totalcost,totalmarketValue,totalunrealizedPnl,totalunrealizedPnl,totalreturPrecentage,totalRealizedPnl,positions)
    };
}