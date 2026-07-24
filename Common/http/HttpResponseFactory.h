#pragma once
#include <boost\beast.hpp>
#include "../IJsonSerializer.h"

namespace http=boost::beast::http;

class HttpResponseFactory
{
private:
    IJsonSerializer& m_serializer;

    http::response<http::string_body> BuildResponse(http::status status,
        const std::string& body,
        const http::request<http::string_body>& request)const;
public:
    explicit HttpResponseFactory(IJsonSerializer& serializer);
    template<typename T>    
    http::response<http::string_body> OK(const T& value,const http::request<http::string_body>& request)const{
        auto json=m_serializer.SerializeObject(value);
        return BuildResponse(http::status::ok,std::move(json),request);
    }
    template<typename T>
    http::response<http::string_body> Create(const T& value, const http::request<http::string_body>& request)const{
        auto json=m_serializer.SerializeObject(value);
        return BuildResponse(http::status::ok,std::move(json),request);
    }
    http::response<http::string_body> BadRequest(const std::vector<std::string>& errors,const http::request<http::string_body>&)const;
    http::response<http::string_body> NotFound(const std::string& body,const http::request<http::string_body>&)const;
    http::response<http::string_body> InterServerError(const std::string& body,const http::request<http::string_body>&)const;
    
};
