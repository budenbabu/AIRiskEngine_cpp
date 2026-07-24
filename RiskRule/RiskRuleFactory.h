#pragma once
#include <memory>
#include "../RiskRule/RiskResult.h"
#include "IRiskRule.h"
#include "../Service/IPortfolioService.h"

class RiskRuleFactory {
    using Creator = std::function<std::unique_ptr<IRiskRule>(const RiskRuleEntity&)>;
    std::unordered_map<ns::RiskViolation,Creator>  m_creators;
public:
    RiskRuleFactory(IPortfolioService& service);
	std::unique_ptr<IRiskRule> Create(const RiskRuleEntity& entity)const;
};
