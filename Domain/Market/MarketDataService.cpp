#include "MarketDataService.h"


MarketDataService::MarketDataService(IMarketEvents& event):m_event(event)
{
    m_quotes.emplace("AAPL",ns::Quote{"AAPL",194.40,194.60,194.50});
    m_symbols.push_back("AAPL");
    m_quotes.emplace("MSFT", ns::Quote{"MSFT",525.10,525.40,525.25});
    m_symbols.push_back("MSFT");
    m_quotes.emplace("NVDA", ns::Quote{"NVDA",181.80,182.00,181.90});
    m_symbols.push_back("NVDA");
    m_quotes.emplace("GOOGL",ns::Quote{"GOOGL",169.20,169.40,169.30});
    m_symbols.push_back("GOOGL");
    m_quotes.emplace("TSLA",ns::Quote{"TSLA",310.20,310.40,309.30});
    m_symbols.push_back("TSLA");
}

std::optional<ns::Quote> MarketDataService::GetQuote(const std::string &symbol) const
{
    std::shared_lock lock(m_mtx);
    auto it=m_quotes.find(symbol);
    if(it==m_quotes.end()) return std::nullopt;    
    return it->second;    
}

std::vector<ns::Quote> MarketDataService::GetQuote() const
{
    std::shared_lock lock(m_mtx);
    std::vector<ns::Quote> results;
    results.reserve(m_quotes.size());
    for(const auto& [symbol,quote] : m_quotes) results.push_back(quote);
    return results;
}

void MarketDataService::UpdateQuote(const ns::Quote &quote)
{
    std::unique_lock lock(m_mtx);
    m_quotes[quote.symbol]=quote;    
    m_event.publisherPriceUpdated(PriceUpdatedEvent{quote});
}

bool MarketDataService::TryGetQuote(const std::string &symbol, ns::Quote &quote) const
{
     std::shared_lock lock(m_mtx);
    auto it=m_quotes.find(symbol);
    if(it==m_quotes.end()) return false;    
    quote=it->second;    
    return true;
}

const std::vector<std::string>& MarketDataService::GetQuoteSymbols() const{ return m_symbols; }
