#pragma once
#include "IAIAnalysisService.h"
#include "../../Loogger/ILogger.h"
#include "../../RiskAnalysisService/Repository/IRiskAIAnalysisRepository.h"

class AIAnalysisService: public IAIAnalysisService{
    ILogger& m_logger;
    IRiskAIAnalysisRepository& m_repo;    
public:
    AIAnalysisService(IRiskAIAnalysisRepository& repo,ILogger& logger);
    std::optional<RiskAIAnalysisEntity> getByViolationID(uint64_t vid)override;
    std::optional<RiskAIAnalysisEntity> GetByAnalysisID(uint64_t aid)override;
    std::vector<RiskAIAnalysisEntity> GetAll()override;
};