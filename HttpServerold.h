#pragma once
#include <iostream>
#include "PortfolioController.h"

class HttpServer
{
    PortfolioController& m_controller;
public:
    HttpServer(PortfolioController& controller);
    void Start();
};

HttpServer::HttpServer(PortfolioController& controller):m_controller(controller)
{
    std::cout<<"HttpServer create\n";
}

inline void HttpServer::Start()
{
    std::cout<<"\nServer Started\n\n";
    m_controller.Get();
}
