#pragma once
#include <boost\di.hpp>
#include <boost\asio.hpp>
#include <vector>
#include <memory>
#include <thread>
#include "../Loogger/ILogger.h"
#include "../RouteRegistrar/Router.h"
#include "../Sessions/SessionFactory.h"
#include "../Common/http/HttpResponseFactory.h"
#include "../Domain/Market/IMarketPriceGenerator.h"
#include "../Middleware/ExceptionMiddleware.h"
#include "../Middleware/LoggingMiddleware.h"
#include "../pipeline/RequestPipeline.h"
#include "../Application/WebSocket/WebSocketListener.h"
#include "../Application/StartupServices.h"
#include "../Listener.h"
#include "../HttpServer.h"

namespace net=boost::asio;

class ILogger;


class Application{
    net::io_context& m_ioc;
    net::executor_work_guard<net::io_context::executor_type> m_work;
    
    ILogger& m_logger;
    IRouter& m_router;
    IMarketPriceGenerator& m_generator;
    HttpResponseFactory& m_httpfactory;
    StartupServices& m_startup;
    WebSocketListener& m_wsListener;

    SessionFactory m_sessionfactory;
    std::shared_ptr<Listener> m_listener;
    ExceptionMiddleware m_exception;
    LoggingMiddleware m_mlogging;
    RequestPipeline m_pipeline;    
    HttpServer m_server;
    std::vector<std::thread> m_threads;
public: 
      BOOST_DI_INJECT(Application,net::io_context& ioc,(named = ServerPort{}) unsigned short port, 
          ILogger& logger,HttpResponseFactory& httpfactory,IRouter& router,IMarketPriceGenerator& generator,
          StartupServices& startup,WebSocketListener& wsListener):m_ioc(ioc),m_work(net::make_work_guard(ioc)),
          m_logger(logger),m_router(router),m_httpfactory(httpfactory),m_generator(generator),m_startup(startup),m_wsListener(wsListener),
          m_exception(router,httpfactory),m_mlogging(m_exception,logger),m_pipeline(m_mlogging),m_sessionfactory(m_pipeline),
          m_listener(std::make_shared<Listener>(ioc,port,m_sessionfactory)),m_server(ioc,m_listener)
      {
          m_logger.Info(std::format("Server port: {}",port));   
      }
    //Application(boost::asio::io_context& ioc,IHttpServer& server,ILogger& logger);
    // Application(net::io_context& ioc, unsigned short port, 
    //       ILogger& logger,HttpResponseFactory& httpfactory,IRouter& router,IMarketPriceGenerator& generator,
    //       StartupServices& startup,WebSocketListener& wsListener);
    void Run();
    void stop();
};