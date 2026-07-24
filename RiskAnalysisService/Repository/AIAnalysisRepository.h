#pragma once

#include<format>
#include "IAIAnalysisRepository.h"
#include "../../Database/PostgreSqlConnectionPool.h"
#include "../../Loogger/ILogger.h"

class AIAnalysisRepository : public IAIAnalysisRepository {
    PostgreSqlConnectionPool& m_pool;
    ILogger& m_logger;
public:
    AIAnalysisRepository(PostgreSqlConnectionPool& pool, ILogger& logger);
    void Save(const ns::AIAnalysis&)override;
    std::optional<ns::AIAnalysis> GetByJobId(uint64_t jobId)override;
    std::vector<ns::AIAnalysis> GetByViolationId(uint64_t vid)override;
};