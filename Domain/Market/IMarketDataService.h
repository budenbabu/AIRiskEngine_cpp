#pragma once
#include "Quote.h"
#include <optional>

class IMarketDataService{
public:
    virtual ~IMarketDataService()=default;
    virtual std::optional<ns::Quote> GetQuote(const std::string& symbol)const=0;
    virtual const std::vector<std::string>& GetQuoteSymbols()const=0;
    virtual std::vector<ns::Quote> GetQuote()const=0;
    virtual void UpdateQuote(const ns::Quote& quote)=0;
    virtual bool TryGetQuote(const std::string& symbol,ns::Quote& quote) const = 0;
};