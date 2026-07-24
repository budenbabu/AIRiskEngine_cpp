#pragma once

#include "IRouteRegistrar.h"
#include "Router.h"
#include "../Controllers/IRiskRuleController.h"

class RiskRuleRouteRegistrar:public IRouteRegistrar{
    IRiskRuleController& m_controller;
    public:
    explicit RiskRuleRouteRegistrar(IRiskRuleController& controller);
    void RegisterRouter(Router& router)override;
};