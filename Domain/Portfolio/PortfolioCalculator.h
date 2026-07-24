#pragma once
#include "IPortfolioCalculator.h"

class PortfolioCalculator: public IPortfolioCalculator{
public:
    ns::PortfolioSummary CalculateSummary(const std::vector<ns::Position>& positions)const override;
}; 