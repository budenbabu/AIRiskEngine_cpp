#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace ns{

    struct ConcentrationRisk
    {
        std::string symbol;
        double percentage{};
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConcentrationRisk,symbol,percentage)
    };

    struct ConcentrationSummary
    {
        bool isHighRisk{};
        double highestExposure{};
        std::string highestExposureSymbol;
        std::vector<ns::ConcentrationRisk> positions;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConcentrationSummary,highestExposure,positions)
    };
}