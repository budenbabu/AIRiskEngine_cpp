#pragma once

#include<format>
#include "IRiskRuleRepository.h"
#include "../../Loogger/ILogger.h"
#include "../../Database/PostgreSqlConnectionPool.h"
#include "../../RiskRule/RiskRuleFactory.h"

class ILoggger;

class PostgresRiskRuleRepository:public IRiskRuleRepository{
    PostgreSqlConnectionPool& m_pool;
    ILogger& m_logger;    
public:
    PostgresRiskRuleRepository(PostgreSqlConnectionPool& pool,ILogger& m_logger);
    std::vector<std::optional<RiskRuleEntity>> GetAll()const override;
    bool Add(const RiskRuleEntity& rule) override;
    bool update(const RiskRuleEntity& rule) override;
    bool Delete(std::uint64_t id) override;    
};