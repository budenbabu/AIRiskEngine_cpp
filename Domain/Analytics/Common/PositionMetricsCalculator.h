#pragma once
#include "IPositionMetricsCalculator.h"

class PositionMetricsCalculator:public IPositionMetricsCalculator{
public:
    PositionMetricsCalculator();
    PositionMetrics Calculate(const ns::Position& position)const override;
};
