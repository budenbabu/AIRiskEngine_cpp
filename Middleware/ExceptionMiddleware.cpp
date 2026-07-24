#include "ExceptionMiddleware.h"

ExceptionMiddleware::ExceptionMiddleware(IRequestHandler& next, HttpResponseFactory &factory):
    Middleware(next),m_factory(factory){}

void ExceptionMiddleware::Handler(RequestContext& context)
{
    try{
        
        InvokeNext(context);
        
    }
    catch(const std::exception& ex){ 
        
        context.setResponse(m_factory.InterServerError(ex.what(),context.GetRequest())); 
    }
    catch(...){          
        context.setResponse(m_factory.InterServerError("Unknow exception",context.GetRequest()));   }    
}
