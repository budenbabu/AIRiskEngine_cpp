#pragma once
#include <string>
#include <sstream>
#include <chrono>

#include "Middleware.h"
#include "../Loogger/ILogger.h"

class LoggingMiddleware: public Middleware{
    ILogger& m_logger;
public:
    LoggingMiddleware(IRequestHandler& next,ILogger& logger);
    void Handler(RequestContext& context)override;
};

class ScopedTimer{    
    std::chrono::steady_clock::time_point m_start;
public:
    using Callback=std::function<void(std::chrono::milliseconds)>;
    explicit ScopedTimer(Callback callback):m_callback(std::move(callback)),
        m_start(std::chrono::steady_clock::now()){}
    ~ScopedTimer(){
        auto end=std::chrono::steady_clock::now();
        m_callback(std::chrono::duration_cast<std::chrono::milliseconds>(m_start-end));
    }
private:
    Callback m_callback;
};