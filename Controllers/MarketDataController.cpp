#include "MarketDataController.h"


MarketDataController::MarketDataController(IMarketDataService &dataService, HttpResponseFactory &factory,ILogger& logger):
    m_dataService(dataService),m_factory(factory),m_logger(logger){}

http::response<http::string_body> MarketDataController::GetQuotes(const http::request<http::string_body> &request)
{
    auto quotes=m_dataService.GetQuote();    
    for(auto& quote : quotes){
        std::ostringstream ss;
        ss<<quote.symbol<<" "<<quote.ask<<" "<<quote.bid<<" "<<quote.last<<"\n";
        m_logger.Info(ss.str());
    }
    return m_factory.OK(quotes,request);
}

http::response<http::string_body> MarketDataController::GetQuote(const http::request<http::string_body> &request, const std::string &symbol)
{
    ns::Quote quote;
    if(!m_dataService.TryGetQuote(symbol,quote)) m_factory.NotFound("Symbol not found",request);
    return m_factory.OK(quote,request);
}
