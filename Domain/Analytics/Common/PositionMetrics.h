#pragma once

#include <string>

struct PositionMetrics
{
    std::string symbol;
    int quantity = 0;
    double averagePrice = 0.0;
    double marketPrice = 0.0;
    double cost = 0.0;
    double marketValue = 0.0;
    double unrealizedPnL = 0.0;
    double realizedPnl =0.0;
    double returnPercentage = 0.0;
};