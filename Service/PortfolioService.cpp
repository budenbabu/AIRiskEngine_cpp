#include "PortfolioService.h"


PortfolioService::PortfolioService(IPortfolioRepository &repository,IMarketDataService& marketData,IPortfolioAnalyticsService& portfoliSrv):
    m_repository(repository),m_marketdata(marketData),m_portfoliSrv(portfoliSrv){}
std::vector<ns::Position> PortfolioService::GetPortfolio()
{
    return m_repository.GePositions();
}

ns::ExposureSummary PortfolioService::GetExposureSummary()
{
    auto positions=m_repository.GePositions();
    return m_portfoliSrv.GetExposureSummary(positions);
}

ns::PnLSummary PortfolioService::GetPnLSummary()
{
    auto positions=m_repository.GePositions();
    return m_portfoliSrv.GetPnlSummary(positions);
}

ns::ConcentrationSummary PortfolioService::GetconcentrationSummary()
{
    auto positions=m_repository.GePositions();
    return m_portfoliSrv.GetConcentrationSummary(positions);    
}

ns::PortfolioSummary PortfolioService::GetSummary()
{
    auto positions=m_repository.GePositions();
    for (auto& pos : positions) {
        auto quote = m_marketdata.GetQuote(pos.symbol);
        if (quote) pos.marketPrice = quote->last;
    }
    return m_portfoliSrv.GetPortfolioSummary(positions);    
}
