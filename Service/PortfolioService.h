#pragma once
#include "IPortfolioService.h"
#include "../Repository/IPortfolioRepository.h"
#include "../Domain/Portfolio/IPortfolioCalculator.h"
#include "../Domain/Market/IMarketDataService.h"
#include "../Domain/Analytics/Exposures/ExposureCalculator.h"
#include "../Domain/Analytics/IPortfolioAnalyticsService.h"

class PortfolioService final:public IPortfolioService{
    IPortfolioRepository& m_repository;
    IMarketDataService& m_marketdata;
    IPortfolioAnalyticsService& m_portfoliSrv;
    //IPortfolioCalculator& m_Calculator;
    
    //IExposureCalculator& m_exposurecalc;
public:
    explicit PortfolioService(IPortfolioRepository& repository,IMarketDataService& marketData,IPortfolioAnalyticsService& portfoliSrv);
    std::vector<ns::Position> GetPortfolio()override;
    ns::PortfolioSummary GetSummary()override;
    ns::ExposureSummary GetExposureSummary()override;
    ns::PnLSummary GetPnLSummary()override;
    ns::ConcentrationSummary GetconcentrationSummary()override;
    
};