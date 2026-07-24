#pragma once
#include <boost\beast.hpp>
#include <string>

namespace http=boost::beast::http;

struct RouteKey{
    http::verb method;
    std::string path;
    bool operator==(const RouteKey&)const=default;
};

struct RoutKeyHash{
    std::size_t operator()(const RouteKey& key)const{
        std::size_t h1=std::hash<int>{}(static_cast<int>(key.method));
        std::size_t h2=std::hash<std::string>{}(key.path);
        return h1^(h2<<1);
        //return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};