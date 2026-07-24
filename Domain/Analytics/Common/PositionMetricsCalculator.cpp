#include "PositionMetricsCalculator.h"

PositionMetricsCalculator::PositionMetricsCalculator(){}

PositionMetrics PositionMetricsCalculator::Calculate(const ns::Position &position) const
{
    PositionMetrics metrics;

    metrics.symbol = position.symbol;

    metrics.quantity = position.quantity;

    metrics.averagePrice = position.averagePrice;

    metrics.marketPrice = position.marketPrice;

    metrics.cost =
        position.quantity *
        position.averagePrice;

    metrics.marketValue =
        position.quantity *
        position.marketPrice;

    metrics.unrealizedPnL = metrics.marketValue - metrics.cost;
    metrics.realizedPnl=position.realizedPnl;
    if (metrics.cost != 0.0)
    {
        metrics.returnPercentage =
            metrics.unrealizedPnL /
            metrics.cost * 100.0;
    }
    return metrics;
}
