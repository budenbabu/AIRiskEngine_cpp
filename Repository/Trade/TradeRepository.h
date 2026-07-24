#pragma once

#include <shared_mutex>
#include <memory>
#include <atomic>
#include <unordered_map>
#include <algorithm>
#include "ITradeRepository.h"


class TradeRepository:public ITradeRepository{
    mutable std::shared_mutex mtx;
    std::atomic_uint64_t m_nextTradeId{1};
    std::unordered_map<std::uint64_t,ns::Trade> m_TradebyId;
    std::unordered_map<std::string,std::vector<std::uint64_t>> m_TradebySymbol;    
public:
    TradeRepository();
    bool Add(const ns::Trade& trade) override;
    std::optional<ns::Trade> GetById(std::uint64_t tradeId) const override;
    std::vector<ns::Trade> GetBySymbol(const std::string& symbol) const override;
    std::vector<ns::Trade> GetAll() const override;
    bool Exists(std::uint64_t tradeId) const override;
    bool Add(pqxx::transaction_base& tx,const ns::Trade& trade)override;

    // We'll implement this later as CancelTrade()
    bool Remove(std::uint64_t tradeId)override;
};