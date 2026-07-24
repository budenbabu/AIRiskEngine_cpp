#pragma once
#include <vector>
#include "../Models/Position.h"
#include "../Domain/Portfolio/PortfolioSummary.h"
#include "../Domain/Analytics/Exposures/ExposureSummary.h"
#include "../Domain/Analytics/PnL/PnL.h"
#include "../Domain/Risk/Concentration/ConcentrationRisk.h"

class IPortfolioService{
public:
    virtual ~IPortfolioService()=default;
    virtual std::vector<ns::Position> GetPortfolio()=0;
    virtual ns::PortfolioSummary GetSummary()=0;
    virtual ns::ExposureSummary GetExposureSummary()=0;
    virtual ns::PnLSummary GetPnLSummary()=0;
    virtual ns::ConcentrationSummary GetconcentrationSummary()=0;
};