#pragma once
#include <boost\beast\http.hpp>

namespace http=boost::beast::http;

class IRouter
{
public:    
    virtual ~IRouter()=default;
    virtual http::response<http::string_body> Route(const http::request<http::string_body>& request)=0;
};

class IHealthController{
public:
    virtual ~IHealthController()=default;
    virtual http::response<http::string_body> getHealth()=0;
};