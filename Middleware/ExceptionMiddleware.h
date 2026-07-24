#pragma once
#include <format>
#include "Middleware.h"
#include "IRequestHandler.h"
#include "../Common/http/HttpResponseFactory.h"
#include "../Loogger/ILogger.h"

class ExceptionMiddleware:public Middleware{
    HttpResponseFactory& m_factory;    
public:
    ExceptionMiddleware(IRequestHandler& next,HttpResponseFactory& factory);
    void Handler(RequestContext& context)override;
};