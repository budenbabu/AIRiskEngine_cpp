#include "MarketPriceGenerator.h"

void MarketPriceGenerator::Schedule()
{
    m_timer.expires_after(std::chrono::seconds(1));
    m_timer.async_wait(boost::beast::bind_front_handler(&MarketPriceGenerator::OnTimer,shared_from_this()));
}

void MarketPriceGenerator::OnTimer(const boost::system::error_code &ec)
{
    if(ec) return;
    if(!m_runnnig) return;
    GeneratePrice();
    Schedule(); 
}

void MarketPriceGenerator::GeneratePrice()
{
    auto symbols = m_dataService.GetQuoteSymbols();
    for (const auto& symbol : symbols)
    {
        ns::Quote quote;

        if (!m_dataService.TryGetQuote(symbol, quote))
            continue;
        quote.last += m_delta(m_rng);
        if (quote.last < 1.0)
            quote.last = 1.0;
        constexpr double spread = 0.10;
        quote.bid = quote.last - spread / 2.0;
        quote.ask = quote.last + spread / 2.0;
        m_dataService.UpdateQuote(quote);
    }
}

MarketPriceGenerator::MarketPriceGenerator(boost::asio::io_context &ioc, IMarketDataService &dataService) : m_timer(ioc), m_dataService(dataService), m_rng(std::random_device{}()), m_delta(-0.05, 0.50) {}

void MarketPriceGenerator::Start()
{
    if(m_runnnig) return;
    m_runnnig=true;
    Schedule();
}

void MarketPriceGenerator::End()
{
    m_runnnig=false;
    //boost::system::error_code ec;
    m_timer.cancel();
}
