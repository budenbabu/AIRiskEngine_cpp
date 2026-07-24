#pragma once
#include "../Repository/IRiskAIAnalysisRepository.h"
#include "../../Repository/Risk/Violation/IRiskViolationRepository.h"
#include "../ai/IAIService.h"
#include "../../Loogger/ILogger.h"
#include "IRiskAIAnalysisService.h"

class RiskAIAnalysisService:public IRiskAIAnalysisService
{
	ILogger& m_logger;
	IAIService& m_service;
	IRiskViolationRepository& m_vrepo;
	IRiskAIAnalysisRepository& m_arepo;

public:	
	
	RiskAIAnalysisService(IRiskViolationRepository& vrepo, IRiskAIAnalysisRepository& arepo, IAIService& service, ILogger& logger);
	void Analysis(std::uint64_t vid) override;
};

