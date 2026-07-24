#pragma once
#include<iostream>

struct Host_Tag{};
struct Port_Tag{};

class Config{
    std::string m_host;
    int m_port;
public:
    BOOST_DI_INJECT(Config, (named = Host_Tag{}) std::string host, (named = Port_Tag{}) int port)
        : m_host(std::move(host)), m_port(port) {}

    void Print()const{
        std::cout<<m_host<<" "<<m_port<<"\n";
    }
};

class Server{
    Config& m_config;
public:
    Server(Config& config):m_config(config){}
    void Start(){
        m_config.Print();
    }
};