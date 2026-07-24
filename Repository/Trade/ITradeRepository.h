#pragma once

#include <pqxx\pqxx>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../../Domain/Trade/Trade.h"

class ITradeRepository
{
public:
    virtual ~ITradeRepository() = default;
    virtual bool Add(const ns::Trade& trade) = 0;
    virtual std::optional<ns::Trade> GetById(std::uint64_t tradeId) const = 0;
    virtual std::vector<ns::Trade> GetBySymbol(const std::string& symbol) const = 0;
    virtual std::vector<ns::Trade> GetAll() const = 0;
    virtual bool Exists(std::uint64_t tradeId) const = 0;

    virtual bool Add(pqxx::transaction_base& tx,const ns::Trade& trade)=0;
    // We'll implement this later as CancelTrade()
    virtual bool Remove(std::uint64_t tradeId) = 0;
};