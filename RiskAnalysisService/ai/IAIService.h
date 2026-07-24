#pragma once

#include <string>
#include "../../RiskRule//RiskResult.h"
#include "../RiskAIAnalysis.h"


class IAIService {
public:
	virtual ~IAIService() = default;
	virtual ns::AIAnalysisResult AnalysisRisk(const ns::RiskViolationEntity&) = 0;
};