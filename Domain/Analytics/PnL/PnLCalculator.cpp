#include "PnLCalculator.h"


PnLCalculator::PnLCalculator(IPositionMetricsCalculator& mertics):m_mertics(mertics){}

ns::PnLSummary PnLCalculator::Calculate(const std::vector<ns::Position> &poss)const
{
    ns::PnLSummary summary;
    for(const auto& pos: poss){
        auto metrics=m_mertics.Calculate(pos);
        summary.totalcost+=metrics.cost;
        summary.totalmarketValue+=metrics.marketValue;
        summary.totalunrealizedPnl+=metrics.unrealizedPnL;
        summary.totalRealizedPnl+=metrics.realizedPnl;

        summary.positions.push_back({
            metrics.symbol,metrics.cost,
            metrics.marketValue,metrics.unrealizedPnL,
            metrics.returnPercentage,            
            metrics.realizedPnl
        });
    }
    if(summary.totalcost!=0.0)
        summary.totalreturPrecentage=(summary.totalunrealizedPnl/summary.totalcost)*100.0;
    return summary;
}


