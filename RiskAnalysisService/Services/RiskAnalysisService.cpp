#include "RiskAnalysisService.h"





RiskAIAnalysisService::RiskAIAnalysisService(IRiskViolationRepository& vrepo, IRiskAIAnalysisRepository& arepo, IAIService& service, ILogger& logger)
	:m_arepo(arepo),m_logger(logger),m_service(service),m_vrepo(vrepo){}

void RiskAIAnalysisService::Analysis(std::uint64_t vid)
{
	auto violation = m_vrepo.getById(vid);
	if (!violation) return;
	auto result = m_service.AnalysisRisk(*violation);
	RiskAIAnalysisEntity entity = {
		.analysisId=0,
		.violationId = vid,
		.analysis=result.analysis,				
		.recommendation=result.recommendation,
		.modelName="ollam3.2b",
		.confidence=result.confidence,
		.severity=result.severity
	};
	m_arepo.Add(entity);
}
