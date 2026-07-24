#pragma once
#include "Router.h"
#include "IRouteRegistrar.h"
#include "../Controllers/IAIAnalysisController.h"

class AIAnalysisRouteRegistrar: IRouteRegistrar{
    IAIAnalysisController& m_controller;
public:
    AIAnalysisRouteRegistrar(IAIAnalysisController& controller);
    void RegisterRouter(Router& router)override;

};