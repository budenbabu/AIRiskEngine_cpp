#pragma once

#include "../Controllers/IPortfolioController.h"
#include "IRouteRegistrar.h"


class PortfolioRouteRegistrar:public IRouteRegistrar{
    IPortfolioController& m_controller;
    public:
    explicit PortfolioRouteRegistrar(IPortfolioController& controller);
    void RegisterRouter(Router& router)override;
};