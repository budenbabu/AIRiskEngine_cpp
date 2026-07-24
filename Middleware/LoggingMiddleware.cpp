#pragma once
#include "LoggingMiddleware.h"


LoggingMiddleware::LoggingMiddleware(IRequestHandler &next, ILogger &logger):
    Middleware(next),m_logger(logger){}

 void LoggingMiddleware::Handler(RequestContext& context)
{
    auto request=context.GetRequest();
    m_logger.Info("Started " + std::string(request.method_string())+" "+ std::string(request.target()));
    int status=500;
    ScopedTimer timer([&](std::chrono::milliseconds elapsed){
        std::ostringstream oss;
        oss<<"Completed "<<request.method_string()<<" "
            <<request.target()<<" -> "<<status<<" ("<<
            elapsed.count()<<"ms)" ;
    });
    
    InvokeNext(context);
    status= context.GetResponse().result_int();        
}
