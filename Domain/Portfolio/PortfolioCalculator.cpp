#include "PortfolioCalculator.h"

ns::PortfolioSummary PortfolioCalculator::CalculateSummary(const std::vector<ns::Position> &positions) const
{
    ns::PortfolioSummary summary;
    summary.m_totalPositions=positions.size();
    for(const auto& pos: positions){
        summary.m_totalCost+=pos.averagePrice*pos.quantity;
        summary.m_totalMarketValue+=pos.marketPrice*pos.quantity;
    }
    summary.m_totalUnrealizedPnL=summary.m_totalMarketValue-summary.m_totalCost;
    return summary;
}
