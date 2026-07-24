#include "ConcentrationCalculator.h"

#include <algorithm>

ConcentrationCalculator::ConcentrationCalculator(IPositionMetricsCalculator &metreics):m_metrics(metreics){}

ns::ConcentrationSummary ConcentrationCalculator::Calculate(const ns::ExposureSummary &summary) const
{
    ns::ConcentrationSummary result{};
    if(summary.exposures.empty()) return result;

    for(const auto& expos : summary.exposures){
        ns::ConcentrationRisk risk;
        risk.symbol=expos.symbol;
        risk.percentage=expos.percentage;

        result.positions.push_back(risk);
        if (risk.percentage > result.highestExposure)
        {
            result.highestExposure = risk.percentage;
            result.highestExposureSymbol = risk.symbol;
        }
    }

    std::sort(result.positions.begin(),result.positions.end(),
        [](const ns::ConcentrationRisk& lhs,const ns::ConcentrationRisk& rhs){ return lhs.percentage > rhs.percentage; });
    result.isHighRisk=result.highestExposure>=50.0;
    return result;
}
