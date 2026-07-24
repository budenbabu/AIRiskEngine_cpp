#pragma once

#include "IConcentrationCalculator.h"
#include "../../Analytics/Common/IPositionMetricsCalculator.h"

class ConcentrationCalculator:public IConcentrationCalculator
{
    IPositionMetricsCalculator& m_metrics;
public:
    ConcentrationCalculator(IPositionMetricsCalculator& metreics);
    ns::ConcentrationSummary Calculate(const ns::ExposureSummary& summary)const override;    
};