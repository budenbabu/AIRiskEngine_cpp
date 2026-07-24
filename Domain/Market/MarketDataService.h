#pragma once

#include <shared_mutex>
#include <unordered_map>
#include "Quote.h"
#include "IMarketDataService.h"
#include "../../Infrastructure/PriceEvent/IMarketEvents.h"

class MarketDataService: public IMarketDataService{
    std::unordered_map<std::string,ns::Quote> m_quotes;
    std::vector<std::string> m_symbols;
    mutable std::shared_mutex m_mtx;
    IMarketEvents& m_event;
public:
    MarketDataService(IMarketEvents& event);
    std::optional<ns::Quote> GetQuote(const std::string& symbol)const override;
    std::vector<ns::Quote> GetQuote()const override;
    void UpdateQuote(const ns::Quote& quote) override;
    bool TryGetQuote(const std::string& symbol,ns::Quote& quote) const override;
    virtual const  std::vector<std::string>& GetQuoteSymbols()const override;
};