#pragma once
#include <unordered_map>
#include <shared_mutex>
#include <memory>
#include <format>
#include "../Loogger/ILogger.h"
#include "IPortfolioRepository.h"


class InMemoryPortfolioRepository final: public IPortfolioRepository{
    mutable std::shared_mutex mtx;
    std::unordered_map<std::string, ns::Position> m_positions;
    ILogger& m_logger;
public:
    InMemoryPortfolioRepository(ILogger& logger);
    std::vector<ns::Position>  GePositions() const override;
    std::optional<ns::Position>  GetBySymbol(const std::string& symbol) const override;
    bool Add(const ns::Position& position) override;
    bool Update(const ns::Position& position) override;
    bool Remove(const std::string& symbol) override;
    bool UpdateMarketPrice(const std::string& symbol, double marketPrice) override;
    bool Upsert(pqxx::transaction_base& tx,const ns::Position& position)override;
    std::optional<ns::Position>  GetBySymbol(pqxx::transaction_base& tx,const std::string& symbol) const override;
    bool Remove(pqxx::transaction_base& tx,const std::string& symbol) override;
};