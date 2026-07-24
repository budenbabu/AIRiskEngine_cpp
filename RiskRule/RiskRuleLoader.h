#pragma once


#include "RiskRuleFactory.h"
#include "RiskEngine.h"
#include "../Repository/Risk/IRiskRuleRepository.h"
#include "../Loogger/ILogger.h"

class RiskRuleLoader
{
    IRiskRuleRepository& m_repo;
    RiskRuleFactory& m_factory;
    RiskEngine& m_engine;
    ILogger& m_logger;    
public:
    RiskRuleLoader(IRiskRuleRepository& repo, RiskRuleFactory& factory, RiskEngine& m_engine,ILogger& logger);
    void Load();
    void ReLoad();
};