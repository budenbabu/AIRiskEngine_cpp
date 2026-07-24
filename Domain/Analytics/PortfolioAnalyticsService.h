#pragma once
#include "IPortfolioAnalyticsService.h"


class PortfolioAnalyticsService: public IPortfolioAnalyticsService{
    IPortfolioCalculator& m_profoliocalc;
    IExposureCalculator&  m_exposurecalc;    
    IPnLCalculator& m_pnlcalc;
    IConcentrationCalculator& m_concenCalc;
public:
    PortfolioAnalyticsService(IPortfolioCalculator& profoliocalc,IExposureCalculator& exposurecalc,IPnLCalculator& pnlcalc,IConcentrationCalculator& concenCalc);
    ns::PortfolioSummary GetPortfolioSummary(const std::vector<ns::Position>& poss)override;
    ns::ExposureSummary GetExposureSummary(const std::vector<ns::Position>& poss)override;
    ns::PnLSummary GetPnlSummary(const std::vector<ns::Position>& poss)override;
    virtual ns::ConcentrationSummary GetConcentrationSummary(const std::vector<ns::Position>& positions)override;
};