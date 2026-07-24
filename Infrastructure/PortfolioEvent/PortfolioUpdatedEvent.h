#pragma once

#include <nlohmann/json.hpp>
#include "../../Domain/Risk/Concentration/ConcentrationRisk.h"
#include "../../Domain/Analytics/Exposures/ExposureSummary.h"
#include "../../Domain/Analytics/PnL/PnL.h"

namespace ns{
    struct PortfolioUpdatedEvent
    {
       ns::PnLSummary pnl;
       ns::ExposureSummary exposure;
       ns::ConcentrationSummary concenration;
       NLOHMANN_DEFINE_TYPE_INTRUSIVE(PortfolioUpdatedEvent,pnl,exposure,concenration)
    };
}
