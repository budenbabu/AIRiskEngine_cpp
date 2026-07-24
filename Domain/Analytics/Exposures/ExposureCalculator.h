#pragma once
#include "IExposureCalculator.h"
#include "../Common/IPositionMetricsCalculator.h"

class ExposureCalculator: public IExposureCalculator{
    IPositionMetricsCalculator& m_metrics;
public:
    ExposureCalculator(IPositionMetricsCalculator& metrics);
    ns::ExposureSummary Calculate(const std::vector<ns::Position>& positions)const override;
};