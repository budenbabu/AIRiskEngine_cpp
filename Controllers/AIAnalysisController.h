#pragma once

#include "IAIAnalysisController.h"
#include "../Service/AI/AIAnalysisService.h"
#include "../Loogger/ILogger.h"
#include "../Common/http/HttpResponseFactory.h"
#include "../RiskRule/IRiskRule.h"

class AIAnalysisController:public IAIAnalysisController{
    AIAnalysisService& m_service;
    ILogger& m_logger;
    HttpResponseFactory& m_factory;
public:
    AIAnalysisController(AIAnalysisService& service,HttpResponseFactory& factory,ILogger& logger);  
    void getAll(RequestContext&)override;
    void getByVid(RequestContext&)override;
    void getByAid(RequestContext&)override;
};