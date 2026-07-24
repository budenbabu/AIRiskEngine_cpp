#pragma once
#include <boost\beast.hpp>

namespace http=boost::beast::http;

class HttpResponseBuilder{
public:
    static http::response<http::string_body> ok(const std::string& body,unsigned version,bool keeplive);
    static http::response<http::string_body> NotFound(unsigned version,bool keepAlive);
    static http::response<http::string_body> BadRequest(const std::string& body,unsigned version,bool keepalive);
};