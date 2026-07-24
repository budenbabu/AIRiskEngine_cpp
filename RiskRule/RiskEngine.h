#pragma once

#include<memory>
#include <shared_mutex>
#include <vector>
#include "../Loogger/ILogger.h"
#include "IRiskRule.h"
#include "RiskResult.h"

class RiskEngine{    
    mutable std::shared_mutex mtx;
    std::vector<std::unique_ptr<IRiskRule>> m_rules;  
    ILogger& m_logger;  
public:
    RiskEngine(ILogger& logger);
    void AddRule(std::unique_ptr<IRiskRule> rule);
    void ReplaceRules(std::vector<std::unique_ptr<IRiskRule>> rules);
    ns::RiskResult Validate(const ns::Trade& trade,const std::optional<ns::Position>& position)const;
    std::size_t getCount() { return m_rules.size(); }
    void Clear();
};