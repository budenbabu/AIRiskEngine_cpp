#include "RiskRuleFactory.h"
#include "MaxTradeQuantityRule.h"

RiskRuleFactory::RiskRuleFactory(IPortfolioService& service)
{
    m_creators[ns::RiskViolation::MaxPosition] = [](const RiskRuleEntity& e) {
        return std::make_unique<MaxPositionRule>(e.value, e.symbol.value());
    };
    m_creators[ns::RiskViolation::MaxTradeQuantity] = [](const RiskRuleEntity& e) {
        return std::make_unique<MaxTradeQuantityRule>(e.value);
    };
    m_creators[ns::RiskViolation::MaxExposure] = [](const RiskRuleEntity& e) {
        return std::make_unique<MaxExposureRule>(e.value);
    };
    m_creators[ns::RiskViolation::DailyLoss] = [pnl=&service](const RiskRuleEntity& e) {
        return std::make_unique<DailyLossRule>(e.value,*pnl);
    };
}

std::unique_ptr<IRiskRule> RiskRuleFactory::Create(const RiskRuleEntity& entity) const
{
    
    if (auto it = m_creators.find(entity.ruleType); it != m_creators.end()) return it->second(entity);
    throw std::runtime_error(std::format("UnKnown rule type {}", RiskRuleEntity::to_string(entity.ruleType)));

}
