#pragma once

#include <boost/core/ignore_unused.hpp>
#include "ITradeRepository.h"
#include "../../Database/PostgreSqlConnectionPool.h"

class PostgresTradeRepository:public ITradeRepository{
    PostgreSqlConnectionPool& m_db;
    ILogger& m_logger;
    static ns::Trade MapTrade(const pqxx::row& row){
        return{
            .tradeId =row["trade_id"].as<std::uint64_t>(),
            .symbol = row["symbol"].as<std::string>(),
            .side = static_cast<ns::TradeSize>(row["side"].as<int>()),
            .quantity = row["quantity"].as<int>(),
            .price = row["price"].as<double>(),
            .timestamp = row["timestamp"].as<std::uint64_t>()
        };
    }
public:
    PostgresTradeRepository(PostgreSqlConnectionPool& db,ILogger& logger);
    bool Add(const ns::Trade& trade) override;
    std::optional<ns::Trade> GetById(std::uint64_t tradeId) const override;
    std::vector<ns::Trade> GetBySymbol(const std::string& symbol) const override;
    std::vector<ns::Trade> GetAll() const override;
    bool Exists(std::uint64_t tradeId) const override;
    bool Remove(std::uint64_t tradeId) override;
    bool Add(pqxx::transaction_base& tx,const ns::Trade& trade)override;
};