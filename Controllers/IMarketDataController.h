#pragma once
#include <boost\beast.hpp>

namespace http=boost::beast::http;

class IMarketDataController{
public:
    virtual ~IMarketDataController()=default;
    virtual http::response<http::string_body> GetQuotes(const http::request<http::string_body>& request)=0;
    virtual http::response<http::string_body> GetQuote(const http::request<http::string_body>& request,const std::string& symbol)=0;
};