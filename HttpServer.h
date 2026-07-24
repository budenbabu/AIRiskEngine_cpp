#pragma once
#include <iostream>
#include <memory>
#include "Sessions/ISessionFactory.h"
#include "Listener.h"


class IHttpServer{
    public:
    virtual ~IHttpServer()=default;    
    virtual void Stop()=0;
    virtual void Run()=0;
};

class HttpServer: public IHttpServer{
    net::io_context& m_ioc;
    std::shared_ptr<Listener> m_listener;

public:
    HttpServer(net::io_context& ioc, std::shared_ptr<Listener> listener): m_ioc(ioc), m_listener(std::move(listener)) {
        std::cout<<"Http server created\n";
    }
    void Stop() override {
        std::cout<<"Server stopping...\n";
        if (m_listener) {
            m_listener->Stop();
        }
        m_ioc.stop();
    }

    void Run() override {
        m_listener->Run();
        std::cout<<"Server is running.....\n";
        m_ioc.run();
    }
};
