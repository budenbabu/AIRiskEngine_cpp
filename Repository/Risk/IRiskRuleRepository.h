#pragma once
#include <vector>
#include <optional>
#include "../../RiskRule/RiskResult.h"

class IRiskRuleRepository{
public:
    virtual ~IRiskRuleRepository()=default;
    virtual std::vector<std::optional<RiskRuleEntity>> GetAll()const=0;
    virtual bool Add(const RiskRuleEntity& rule) = 0;
    virtual bool update(const RiskRuleEntity& rule) = 0;
    virtual bool Delete(std::uint64_t id) = 0;    
};