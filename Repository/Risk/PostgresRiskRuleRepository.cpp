#include "PostgresRiskRuleRepository.h"


PostgresRiskRuleRepository::PostgresRiskRuleRepository(PostgreSqlConnectionPool &pool,ILogger& logger):
    m_pool(pool),m_logger(logger){}

std::vector<std::optional<RiskRuleEntity>> PostgresRiskRuleRepository::GetAll()const{

    try{
        auto conn = m_pool.Acquire();
        pqxx::read_transaction tx(*conn);
        auto results= tx.exec("SELECT rule_id,rule_type,symbol,rule_value,enabled,description FROM risk_rules ORDER BY rule_id");
        std::vector<std::optional<RiskRuleEntity>> rules;
        rules.reserve(results.size());
        for (const auto& row : results) {
            RiskRuleEntity entity{
                .id = row["rule_id"].as<std::uint64_t>(),
                .ruleType =  RiskRuleEntity::from_string(row["rule_type"].as<std::string>()),
                .symbol = row["symbol"].as<std::string>(),
                .value = row["rule_value"].as<double>(),
                .enabled = row["enabled"].as<bool>(),
                .description=row["description"].as<std::string>()            
             };
            rules.push_back(std::move(entity));
        }            
        m_logger.Info(std::format("Count: {} {}", results.size(),rules.size()));
        return rules;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresRiskRuleRepository::GetAl: exception: {}", ex.what()));
        return {};
    }

}

bool PostgresRiskRuleRepository::Add(const RiskRuleEntity& rule)
{
    try {
        auto conn = m_pool.Acquire();
        pqxx::work tx(*conn);
        tx.exec_prepared("insert_risk_rule",RiskRuleEntity::to_string(rule.ruleType), rule.symbol, rule.value, rule.enabled, rule.description);
        tx.exec("NOTIFY risk_rule_updates,"+tx.quote("reload"));
        tx.commit();
        return true;
    }catch (const std::exception& ex) {
        m_logger.Error(std::format("PostgresRiskRuleRepository::ADD exception: {}", ex.what()));
        return false;
    }
}

bool PostgresRiskRuleRepository::update(const RiskRuleEntity& rule)
{
    try {
        auto conn = m_pool.Acquire();
        pqxx::work tx(*conn);
        auto result= tx.exec_prepared("update_risk_rule",
            RiskRuleEntity::to_string(rule.ruleType), rule.symbol, rule.value, rule.enabled, rule.description, rule.id);
        if (result.affected_rows() == 0) { tx.abort(); return false; }
        tx.exec("NOTIFY risk_rule_updates,'reload'");
        tx.commit();
        return true;
    }catch (const std::exception& ex) {
        m_logger.Error(std::format("PostgresRiskRuleRepository::update exception: {}", ex.what()));
        return false;
    }
}

bool PostgresRiskRuleRepository::Delete(std::uint64_t id)
{
    try {
        auto conn = m_pool.Acquire();
        pqxx::work tx(*conn);
        auto result= tx.exec_prepared("delete_risk_rule", id);
        if (result.affected_rows() == 0) { tx.abort(); return false; }
        tx.exec("NOTIFY risk_rule_updates," + tx.quote("reload"));
        tx.commit();
        return true;
    }catch (const std::exception& ex) {
        m_logger.Error(std::format("PostgresRiskRuleRepository::delete exception: {}", ex.what()));
        return false;
    }
}

