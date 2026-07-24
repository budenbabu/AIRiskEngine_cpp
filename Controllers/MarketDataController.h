#pragma once

#include "IMarketDataController.h"
#include "../Domain/Market/IMarketDataService.h"
#include "../Common/http/HttpResponseFactory.h"
#include "../Loogger/ILogger.h"

class MarketDataController: public IMarketDataController{
    IMarketDataService& m_dataService;
    HttpResponseFactory& m_factory;
    ILogger& m_logger;
public:
    MarketDataController(IMarketDataService& dataService,HttpResponseFactory& factory,ILogger& logger);
    http::response<http::string_body> GetQuotes(const http::request<http::string_body>& request)override;
    http::response<http::string_body> GetQuote(const http::request<http::string_body>& request,const std::string& symbol)override;
};