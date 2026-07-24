#include "ApplicationStartup.h"

ApplicationStartup::ApplicationStartup(net::io_context& ioc,DataBaseConfig& config,IRouter& router,ILogger &logger):m_ioc(ioc),
    m_work(net::make_work_guard(ioc)),m_config(config),m_logger(logger),m_router(router)
{
    m_logger.Info(std::format("Application Startup ... {}",m_config.m_hport));
}

void ApplicationStartup::Run()
{
    std::size_t noThreads=std::max(4u,std::thread::hardware_concurrency());
    m_thread.reserve(noThreads);
    for(int i=0;i<noThreads;++i) m_thread.emplace_back([this]{m_ioc.run();});
    m_logger.Info("Application Running ...");
    for(auto& th: m_thread) th.join();
    
}

void ApplicationStartup::stop()
{
    m_work.reset();
    
    m_logger.Info("Application Stopped ...");
}
