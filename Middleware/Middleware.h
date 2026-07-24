#pragma once

#include "IRequestHandler.h"

class Middleware: public IRequestHandler{

    IRequestHandler& m_next;
public:
    explicit Middleware(IRequestHandler& next):m_next(next){}
    virtual ~Middleware()=default;
protected:
    IRequestHandler& next()const noexcept{ return m_next; }
    
    void InvokeNext(RequestContext& context){ m_next.Handler(context); }
};