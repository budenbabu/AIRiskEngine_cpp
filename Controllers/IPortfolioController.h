#pragma once

#include <boost\beast.hpp>

namespace http=boost::beast::http;

class IPortfolioController{
public:
    virtual ~IPortfolioController()=default;
    virtual http::response<http::string_body> GetPortfolio(const http::request<http::string_body>& request)=0;
    virtual http::response<http::string_body> CreatePortfolio(const http::request<http::string_body>& request)=0;
    virtual http::response<http::string_body> GetSummary(const http::request<http::string_body>& request)=0;
    virtual http::response<http::string_body> GetExposureSummary(const http::request<http::string_body>& request)=0;
    virtual http::response<http::string_body> GetPnLSummary(const http::request<http::string_body>& request)=0;
    virtual http::response<http::string_body> GetconcentrationSummary(const http::request<http::string_body>& request)=0;
};