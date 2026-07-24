#pragma once

#include "IPnLCalculator.h"
#include "../Common/IPositionMetricsCalculator.h"

class PnLCalculator:public IPnLCalculator{
    IPositionMetricsCalculator& m_mertics;
public:
    PnLCalculator(IPositionMetricsCalculator& mertics);
    ns::PnLSummary Calculate(const std::vector<ns::Position>& poss)const override;
};