#pragma once
#include <nlohmann/json.hpp>
namespace ns{  
    struct PortfolioSummary
    {
        double m_totalCost = 0.0;
        double m_totalMarketValue = 0.0;
        double m_totalUnrealizedPnL = 0.0;
        size_t m_totalPositions = 0;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PortfolioSummary,m_totalCost,m_totalMarketValue,m_totalUnrealizedPnL,m_totalPositions)
    };    
}