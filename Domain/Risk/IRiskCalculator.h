#pragma once

#include "RiskSummary.h"
#include "../../Models/Position.h"


class IRiskCalculator {
public:
	virtual ~IRiskCalculator() = default;
	virtual RiskSummary Calculate(const std::vector<ns::Position>&)const = 0;
};