

#include "AIAnalysisService.h"

AIAnalysisService::AIAnalysisService(IRiskAIAnalysisRepository &repo, ILogger &logger):m_repo(repo),m_logger(logger){}

std::optional<RiskAIAnalysisEntity> AIAnalysisService::getByViolationID(uint64_t vid)
{
    return m_repo.GetByViolationID(vid);
}

std::optional<RiskAIAnalysisEntity> AIAnalysisService::GetByAnalysisID(uint64_t aid)
{
    return m_repo.GetByAnalysisID(aid);
}

std::vector<RiskAIAnalysisEntity> AIAnalysisService::GetAll()
{
    return m_repo.GetAll();
}
