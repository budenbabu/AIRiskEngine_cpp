#include "ExposureCalculator.h"

ExposureCalculator::ExposureCalculator(IPositionMetricsCalculator& metrics):m_metrics(metrics){}

ns::ExposureSummary ExposureCalculator::Calculate(const std::vector<ns::Position>& positions) const
{
    std::vector<PositionMetrics> metricsList;
    metricsList.reserve(positions.size());

    ns::ExposureSummary summary;

    for (const auto& position : positions)
    {
        auto metrics = m_metrics.Calculate(position);

        summary.totalMarketValue += metrics.marketValue;

        metricsList.push_back(std::move(metrics));
    }

    if (summary.totalMarketValue == 0.0)
        return summary;

    for (std::size_t i = 0; i < positions.size(); ++i)
    {
        ns::Exposure exposure;

        exposure.symbol = positions[i].symbol;
        exposure.marketValue = metricsList[i].marketValue;
        exposure.percentage =
            metricsList[i].marketValue /
            summary.totalMarketValue * 100.0;

        summary.exposures.push_back(std::move(exposure));
    }

    return summary;
}
