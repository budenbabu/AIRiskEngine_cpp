#include "RiskViolationRepository.h"



RiskViolationRepository::RiskViolationRepository(PostgreSqlConnectionPool& pool, ILogger& logger):
    m_logger(logger),m_pool(pool){}

std::uint64_t RiskViolationRepository::Add(const ns::RiskViolationEntity &violation)
{
    try{
        auto conn = m_pool.Acquire();
        pqxx::work tx(*conn);
        auto rows= tx.exec_prepared("insert_risk_violation",
            violation.timestamp, violation.symbol, RiskRuleEntity::to_string(violation.violation), violation.message, violation.tradeJson);
        tx.commit();
        if (rows.empty()) return 0;
        return rows[0][0].as<std::uint64_t>();
    }catch(const std::exception& ex){
        m_logger.Error(std::format("RiskViolationRepository::Add: {}", ex.what()));
        return false;
    }
    
}

std::vector<ns::RiskViolationEntity> RiskViolationRepository::GetAll() const
{
    std::vector<ns::RiskViolationEntity> result;
    auto conn = m_pool.Acquire();
    pqxx::read_transaction tx(*conn);
    auto rows = tx.exec(R"(select * from risk_violations order by violation_id DESC)");
    result.reserve(rows.size());
    for (auto row : rows) {
        result.push_back({
            .id=row["violation_id"].as<std::uint64_t>(),
            .timestamp=row["timestamp"].as<std::uint64_t>(),
            .symbol=row["symbol"].as<std::string>(),
            .violation=RiskRuleEntity::from_string(row["violation_type"].as<std::string>()),
            .tradeJson=row["trade_json"].as<std::string>()

        });
    }
    return result;
}

std::vector<ns::RiskViolationEntity> RiskViolationRepository::getBySymbol(const std::string& symbol) const
{
    std::vector<ns::RiskViolationEntity> result;
    auto conn = m_pool.Acquire();
    pqxx::read_transaction tx(*conn);
    auto rows = tx.exec_params(R"(SELECT * FROM risk_violations WHERE trade_json->>'symbol'=$1)",symbol);
    result.reserve(rows.size());
    for (auto row : rows) {
        result.push_back({
            .id = row["violation_id"].as<std::uint64_t>(),
            .timestamp = row["timestamp"].as<std::uint64_t>(),
            .symbol = row["symbol"].as<std::string>(),
            .violation = RiskRuleEntity::from_string(row["violation_type"].as<std::string>()),
            .tradeJson = row["trade_json"].as<std::string>()

            });
    }
    return result;
}

std::vector<ns::RiskViolationEntity> RiskViolationRepository::getByType(const std::string& type) const
{
    std::vector<ns::RiskViolationEntity> result;
    auto conn = m_pool.Acquire();
    pqxx::read_transaction tx(*conn);
    auto rows = tx.exec_params(R"( SELECT * FROM risk_violations WHERE violation_type=$1)", type);
    result.reserve(rows.size());
    for (auto row : rows) {
        result.push_back({
            .id = row["violation_id"].as<std::uint64_t>(),
            .timestamp = row["timestamp"].as<std::uint64_t>(),
            .symbol = row["symbol"].as<std::string>(),
            .violation = RiskRuleEntity::from_string(row["violation_type"].as<std::string>()),
            .tradeJson = row["trade_json"].as<std::string>()

            });
    }
    return result;
}

std::optional<ns::RiskViolationEntity> RiskViolationRepository::getById(const std::uint64_t vid)
{
    try {
        auto conn = m_pool.Acquire();
        pqxx::read_transaction tx(*conn);
        auto rows = tx.exec_params(R"( SELECT * FROM risk_violations WHERE violation_id=$1)", vid);
        if (rows.empty()) return std::nullopt;
        auto row = rows[0];
       return ns::RiskViolationEntity {
        .id = row["violation_id"].as<std::uint64_t>(),
        .timestamp = row["timestamp"].as<std::uint64_t>(),
        .symbol = row["symbol"].as<std::string>(),
        .violation = RiskRuleEntity::from_string(row["violation_type"].as<std::string>()),
        .tradeJson = row["trade_json"].as<std::string>()
       };                
    }
    catch (const std::exception& ex) {
        m_logger.Error(std::format("RiskViolationRepository::getById: {}", ex.what()));
        return std::nullopt;
    }
}
