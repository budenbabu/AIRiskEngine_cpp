#pragma once

#include <boost\beast.hpp>
#include <unordered_map>
#include <string>

namespace http=boost::beast::http;

class RequestContext{    
    http::request<http::string_body> m_request;
    std::optional<http::response<http::string_body>> m_response;
    std::chrono::steady_clock::time_point m_startTime;
    std::string m_requestId;
    std::string m_remoteAddress;
    std::string m_username;
    bool m_authenicated=false;
    std::unordered_map<std::string,std::string> m_routeValues;
public:
    explicit RequestContext(http::request<http::string_body> request)
        :m_request(std::move(request)),m_startTime(std::chrono::steady_clock::now()){}

    http::request<http::string_body>& GetRequest(){ return m_request; } 
    const http::request<http::string_body>& GetRequest()const{ return m_request; }
    
    void setResponse(http::response<http::string_body> response){ m_response=std::move(response); }
    http::response<http::string_body>& GetResponse(){ return m_response.value(); }
    const http::response<http::string_body>& GetResponse()const{ return m_response.value(); }
    
    bool HasResonse()const{ return m_response.has_value(); }
    void RequestId(std::string id){ m_requestId=std::move(id); }
    const std::string& RequestId() const { return m_requestId; }
    void RemoteAddress(std::string address){ m_remoteAddress=std::move(address); }
    const std::string& RemoteAddress()const { return m_remoteAddress; }
    std::chrono::steady_clock::time_point StartTime()const{ return m_startTime; }
    void setRouterValue(std::string name,std::string value){
        m_routeValues.emplace(name,value);
    }
    std::optional<std::string> GetrouteValue(const std::string& name)const{
        auto it=m_routeValues.find(name);
        if(it == m_routeValues.end()) return std::nullopt;
        return it->second;
    }
    
};