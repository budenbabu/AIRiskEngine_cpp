#pragma once
#include <boost\beast.hpp>

namespace http=boost::beast::http;

class IHttpResponseFactory{
public:
    virtual ~IHttpResponseFactory()=default;
    virtual http::response<http::string_body> OK(const std::string& body,http::request<http::string_body>&)const=0;
    virtual http::response<http::string_body> Create(const std::string& body,http::request<http::string_body>&)const=0;
    virtual http::response<http::string_body> BadRequest(const std::vector<std::string> error,http::request<http::string_body>&)const=0;
    virtual http::response<http::string_body> NotFound(const std::string& body,http::request<http::string_body>&)const=0;
    virtual http::response<http::string_body> InterServerError(const std::string& body,http::request<http::string_body>&)const=0;
};