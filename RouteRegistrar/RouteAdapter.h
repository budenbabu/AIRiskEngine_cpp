#pragma once

#include "../pipeline/RequestContext.h"

namespace ns
{

//------------------------------------------------------------
// Legacy Controller Adapter
//
// Controller:
// http::response<string_body>
// Method(const http::request<string_body>&);
//
//------------------------------------------------------------

template<typename Controller, typename Method>
auto Adapt(Controller& controller, Method method)
{
    return [&controller, method](RequestContext& context)
    {
        auto response =
            (controller.*method)(context.GetRequest());
        context.setResponse(std::move(response));
        //const_cast<RequestContext&>(context).setResponse(std::move(response));
    };
}

//------------------------------------------------------------
// RequestContext Controller Adapter
//
// Controller:
//
// void Method(RequestContext&);
//
//
//------------------------------------------------------------

template<typename Controller, typename Method>
auto AdaptContext(Controller& controller, Method method)
{
    return [&controller, method](const RequestContext& context)
    {
        (controller.*method)(const_cast<RequestContext&>(context));
    };
}

}