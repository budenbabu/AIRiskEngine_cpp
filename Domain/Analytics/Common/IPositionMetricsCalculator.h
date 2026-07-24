#pragma once

#include "PositionMetrics.h"
#include "../../../Models/Position.h"

class IPositionMetricsCalculator
{
public:
    virtual ~IPositionMetricsCalculator() = default;
    virtual PositionMetrics Calculate(const ns::Position& position) const = 0;
};