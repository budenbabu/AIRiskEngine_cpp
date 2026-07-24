#pragma once

#include <vector>
#include "../Portfolio/PortfolioSummary.h"
#include "../../Models/Position.h"
#include "Exposures/ExposureSummary.h"
#include "../Portfolio/IPortfolioCalculator.h"
#include "Exposures/IExposureCalculator.h"
#include "PnL/IPnLCalculator.h"
#include "../Risk/Concentration/ConcentrationRisk.h"
#include "../Risk/Concentration/IConcentrationCalculator.h"

class IPortfolioAnalyticsService{
public:
    virtual ~IPortfolioAnalyticsService()=default;
    virtual ns::PortfolioSummary GetPortfolioSummary(const std::vector<ns::Position>& postion)=0;
    virtual ns::ExposureSummary GetExposureSummary(const std::vector<ns::Position>& positions)=0;
    virtual ns::PnLSummary GetPnlSummary(const std::vector<ns::Position>& positions)=0;
    virtual ns::ConcentrationSummary GetConcentrationSummary(const std::vector<ns::Position>& positions)=0;  
};