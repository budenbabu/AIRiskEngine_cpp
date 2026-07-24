#pragma once
#include "../pipeline/RequestContext.h"


class IRiskRuleController {
public:
	virtual ~IRiskRuleController() = default;
	virtual void getRules(RequestContext& context) = 0;
	virtual void addRule(RequestContext& context) = 0;
	virtual void updatedRule(RequestContext& context) = 0;
	virtual void deleteRule(RequestContext& context) = 0;
	virtual void riskViolation(RequestContext& context) = 0;
	virtual void riskViolationBySymbol(RequestContext& context) = 0;
	virtual void riskViolationByType(RequestContext& context) = 0;
	virtual void GenerateAnalysis(RequestContext& context) = 0;
};