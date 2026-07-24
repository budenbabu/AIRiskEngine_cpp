#pragma once

#include <boost\core\ignore_unused.hpp>
#include "IPortfolioRepository.h"
#include "../Database/PostgreSqlConnectionPool.h"

class PostgresPortfolioRepository: public IPortfolioRepository{
    PostgreSqlConnectionPool& m_db;
    ILogger& m_logger;
    static ns::Position MapPostion(const pqxx::row& row){
        return{            
            .symbol = row["symbol"].as<std::string>(),
            .quantity = row["quantity"].as<int>(),
            .averagePrice = row["avg_price"].as<double>(),
            .marketPrice=row["market_price"].as<double>(),            
            .realizedPnl = row["realized_pnl"].as<double>()
        };
    }
public:
    PostgresPortfolioRepository(PostgreSqlConnectionPool& db,ILogger& logger);
    std::vector<ns::Position>  GePositions() const override;
    std::optional<ns::Position>  GetBySymbol(const std::string& symbol) const override;
    bool Add(const ns::Position& position) override;
    bool Update(const ns::Position& position) override;
    bool Remove(const std::string& symbol) override;
    bool UpdateMarketPrice(const std::string& symbol,double marketPrice) override;
    bool Upsert(pqxx::transaction_base& tx,const ns::Position& position)override;
    std::optional<ns::Position>  GetBySymbol(pqxx::transaction_base& tx,const std::string& symbol) const override;
    bool Remove(pqxx::transaction_base& tx,const std::string& symbol) override;
    std::optional<ns::Position> GetBySymbolForUpdate(pqxx::transaction_base& tx,const std::string& symbol)override;
};