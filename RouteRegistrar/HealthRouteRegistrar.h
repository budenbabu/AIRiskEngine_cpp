#pragma once

#include "IRouteRegistrar.h"
#include "Router.h"

class IHealthController;
class Router;

class HealthRouteRegistrar : public IRouteRegistrar {
    IHealthController& m_controller;    
public:
    explicit HealthRouteRegistrar(IHealthController& controller);
    void RegisterRouter(Router& router) override;
};

