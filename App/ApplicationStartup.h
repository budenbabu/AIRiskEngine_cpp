#pragma once
#include <boost\asio.hpp>
#include <vector>
#include <thread>
#include <format>
#include "IApplicationStartup.h"
#include "../Loogger/ILogger.h"
#include "../Database/DatabaseConfig.h"
#include "../RouteRegistrar/Router.h"

namespace net=boost::asio;

class ApplicationStartup: public IApplicationStartup{
    ILogger& m_logger;
    net::executor_work_guard<net::io_context::executor_type> m_work;
    std::vector<std::thread> m_thread;
    DataBaseConfig& m_config;
    IRouter& m_router;
    net::io_context& m_ioc;
public:
    ApplicationStartup(net::io_context& ioc,DataBaseConfig& config,IRouter& router,ILogger& logger);
    void Run()override; 
    void stop()override;
};