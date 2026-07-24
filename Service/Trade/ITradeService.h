#pragma once

#include "../../Domain/Trade/Trade.h"


class ITradeService{
public:
    virtual ~ITradeService()=default;
    virtual bool Execute(const ns::Trade& trade)=0;
    virtual std::vector<ns::Trade> GetTrades() const = 0;
    virtual std::optional<ns::Trade> GetTrade(std::uint64_t tradeId) const = 0;
    virtual std::vector<ns::Trade> GetSymbolBytrade(const std::string& symbol)const=0;
};