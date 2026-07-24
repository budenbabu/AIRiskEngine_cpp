#pragma once

#include <vector>

#include "..\..\Models\Position.h"
#include "PortfolioSummary.h"

class IPortfolioCalculator
{
public:
    virtual ~IPortfolioCalculator() = default;

    virtual ns::PortfolioSummary CalculateSummary(const std::vector<ns::Position>& positions) const = 0;
};