#pragma once
#include <boost\beast.hpp>
#include "../pipeline/RequestContext.h"

namespace http=boost::beast::http;

class IRequestHandler{
public:
    virtual ~IRequestHandler()=default;
    //virtual http::response<http::string_body> Handler(const http::request<http::string_body>& request)=0;
    virtual void Handler(RequestContext&)=0;
};