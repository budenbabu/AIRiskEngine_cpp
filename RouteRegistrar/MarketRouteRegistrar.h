#pragma once

#include "IRouteRegistrar.h"
#include "../Controllers/IMarketDataController.h"
#include "Router.h"

class IMarketDataController;
class Router;

class MarketRouteRegistrar : public IRouteRegistrar {
    IMarketDataController& m_controller;    
public:
    explicit MarketRouteRegistrar(IMarketDataController& controller);
    void RegisterRouter(Router& router) override;
};