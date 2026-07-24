#pragma once
#include <string>
#include "../../RiskRule/RiskResult.h"

class PromptBuilder {
public:
	static std::string BuildRiskAnalysisPrompt(const ns::RiskViolationEntity&);
};
