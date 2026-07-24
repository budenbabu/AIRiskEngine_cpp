#include "RiskEngine.h"

RiskEngine::RiskEngine(ILogger &logger):m_logger(logger)
{
}

void RiskEngine::AddRule(std::unique_ptr<IRiskRule> rule)
{
    std::unique_lock lock(mtx);
    m_rules.push_back(std::move(rule));
}

ns::RiskResult RiskEngine::Validate(const ns::Trade &trade, const std::optional<ns::Position> &position) const
{
    std::shared_lock lock(mtx);
    for(const auto& rule : m_rules){        
        m_logger.Info(std::format("Validating {}",typeid(*rule).name()));
        auto result=rule->Validate(trade,position);
        if(!result){
            return result;
        }
    }
    return ns::RiskResult::Allow();
}


void RiskEngine::ReplaceRules(std::vector<std::unique_ptr<IRiskRule>> rules) {
    std::unique_lock lock(mtx);
    m_rules = std::move(rules);
}

void RiskEngine::Clear()
{
    std::unique_lock lock(mtx);
    m_rules.clear();
}
