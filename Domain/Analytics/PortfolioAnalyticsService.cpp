#include "PortfolioAnalyticsService.h"



PortfolioAnalyticsService::PortfolioAnalyticsService(IPortfolioCalculator &profoliocalc, 
    IExposureCalculator &exposurecalc,IPnLCalculator& pnlcalc,IConcentrationCalculator& concenCalc):m_pnlcalc(pnlcalc),
    m_exposurecalc(exposurecalc),m_profoliocalc(profoliocalc),m_concenCalc(concenCalc){}

ns::PortfolioSummary PortfolioAnalyticsService::GetPortfolioSummary(const std::vector<ns::Position> &poss)
{
    return m_profoliocalc.CalculateSummary(poss);
}

ns::ExposureSummary PortfolioAnalyticsService::GetExposureSummary(const std::vector<ns::Position> &poss)
{
    return m_exposurecalc.Calculate(poss);
}

ns::PnLSummary PortfolioAnalyticsService::GetPnlSummary(const std::vector<ns::Position> &poss)
{
    return m_pnlcalc.Calculate(poss);    
}

ns::ConcentrationSummary PortfolioAnalyticsService::GetConcentrationSummary(const std::vector<ns::Position> &positions)
{
    auto summary=m_exposurecalc.Calculate(positions);
    return m_concenCalc.Calculate(summary);;
}
