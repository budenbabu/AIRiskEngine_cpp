#include "Application.h"

//net::io_context* IoContextProvider::instance = nullptr;

//Application::Application(boost::asio::io_context &ioc, IHttpServer &httpServer, ILogger &logger, WebSocketListener &wsListener, IMarketPriceGenerator &generator, StartupServices &startupServices):
//    m_ioc(ioc),m_work(boost::asio::make_work_guard(m_ioc)),
//    m_httpServer(httpServer),m_logger(logger),m_generator(generator),m_wslistener(wsListener),
//    m_startupServices(startupServices)
//{
//}
// void Application::Run()
// {
//     m_generator.Start();
//     m_wslistener.run();
//     m_httpServer.Run();
//     auto threadCount=std::max(2u,std::thread::hardware_concurrency());
//     m_logger.Info(std::format("Starting {} worker thres",threadCount));
//     m_threads.reserve(threadCount);
//     for(unsigned i=0;i<threadCount;++i) m_threads.emplace_back([this]{ m_ioc.run(); });
//     for(auto& th: m_threads) th.join();
// }
// void Application::stop()
// {
//     m_logger.Info("Stopping application");
//     m_generator.End();    
//     m_httpServer.Stop();
// }


// Application::Application(boost::asio::io_context& ioc,unsigned short ServerPort,ILogger& logger):m_ioc(ioc),m_logger(logger)
// {
    // m_logger.Info(std::format("Port: {}",ServerPort));
// }

//Application::Application(boost::asio::io_context &ioc, IHttpServer &server,ILogger& logger):
//    m_ioc(ioc),m_work(net::make_work_guard(ioc)),m_server(server),m_logger(logger)
//{
//}

// Application::Application(net::io_context & ioc,unsigned short port, ILogger& logger, HttpResponseFactory & httpfactory, IRouter & router, 
//     IMarketPriceGenerator & generator, StartupServices & startup, WebSocketListener & wsListener):
//     m_ioc(ioc),m_work(net::make_work_guard(ioc)),
//     m_logger(logger),m_router(router),m_httpfactory(httpfactory),m_generator(generator),m_startup(startup),m_wsListener(wsListener),
//     m_exception(router,httpfactory),m_mlogging(m_exception,logger),m_pipeline(m_mlogging),m_sessionfactory(m_pipeline),
//     m_listener(std::make_shared<Listener>(ioc,port,m_sessionfactory)),m_server(ioc,m_listener){}

void Application::Run()
{
    m_generator.Start();
    m_wsListener.run();
    m_server.Run();
    
    auto threadCount=std::max(4u,std::thread::hardware_concurrency()-2);
    for(unsigned int i=0;i<threadCount;++i)
        m_threads.emplace_back([this]{m_ioc.run();});
    
    for(auto& th: m_threads) th.join();
}

void Application::stop()
{
    m_work.reset();
    m_generator.End();
    m_work.reset();    
    m_server.Stop();
    
    
}
