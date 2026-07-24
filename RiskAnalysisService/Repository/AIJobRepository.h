#pragma once

#include <format>
#include "IAIJobRepository.h"
#include "../../Database/PostgreSqlConnectionPool.h"
#include "../../Loogger/ILogger.h"

class AIJobRepository:public IAIJobRepository{
    PostgreSqlConnectionPool& m_pool;
    ILogger& m_logger;
public:
    AIJobRepository(PostgreSqlConnectionPool& pool,ILogger& logger);
    uint64_t Create(uint64_t violationId)override;
    void updateStatus(uint64_t jobid,ns::AIJobStatus status)override;
    void IncrementRetry(uint64_t jobid)override;
    void MakeFailed(uint64_t jobid,const std::string& error)override;
    std::vector<ns::AIJob> GetPendingJobs()override;
};