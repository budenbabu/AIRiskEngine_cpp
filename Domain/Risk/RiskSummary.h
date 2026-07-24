#pragma once
#include <vector>

#include "../Analytics/Exposures/Exposure.h"

struct RiskSummary
{
	double totalMarketValue{};
	std::vector<ns::Exposure> exposures;
};