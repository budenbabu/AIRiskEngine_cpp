#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include "Exposure.h"

namespace ns
{
    struct ExposureSummary{
        double totalMarketValue=0.0;
        std::vector<ns::Exposure> exposures;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExposureSummary,totalMarketValue,exposures)
    };  
}

