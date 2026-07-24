#pragma once
#include "../Middleware/IRequestHandler.h"

class RequestPipeline: public IRequestHandler{
    IRequestHandler& m_frist;
public:
    explicit RequestPipeline(IRequestHandler& frist):m_frist(frist){}
    //http::response<http::string_body> Handler(const http::request<http::string_body>& request)override{ return m_frist.Handler(request); }
    void Handler(RequestContext& context)override{ m_frist.Handler(context); }
};