#include "PromptBuilder.h"

std::string PromptBuilder::BuildRiskAnalysisPrompt(const ns::RiskViolationEntity& v)
{
    
	std::stringstream ss;

	ss << R"(You are a senior trading risk analyst.
    
    Analyze the following risk violation.
    
    Violation Type:
    )"
		<< RiskRuleEntity::to_string(v.violation)
		<< R"(
    
    Violation Message:
    )"
		<< v.message
		<< R"(
    
    Trade Information:
    )"
		<< v.tradeJson
		<< R"(
    
    Provide:
    
    1. Explanation
    2. Possible cause
    3. Recommendation
    4. Severity
    5. confidence

    Return ONLY JSON.

    {
       "analysis":"",
       "recommendation":"",
       "model":""
       "severity":"",
        "confidence":0.0
    }
    )";

	return ss.str();

}
