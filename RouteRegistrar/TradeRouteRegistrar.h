#pragma once



#include "Router.h"
#include "../Controllers/ITradeController.h"
#include "../pipeline/RequestContext.h"


class TradeRouteRegistrar: public IRouteRegistrar{
    ITradeController& m_controller;
public:
    TradeRouteRegistrar(ITradeController& controller);
    void RegisterRouter(Router& route)override;
};


