#pragma once

#include <boost/core/ignore_unused.hpp>

#include "IAIJobRepository.h"
#include "../../../Database/PostgreSqlConnectionPool.h" 
#include "../../../Loogger/ILogger.h"

class AIJobRepository :public IAIJobRepository {
	PostgreSqlConnectionPool& m_pool;
	ILogger& m_logger;
public:
	AIJobRepository(PostgreSqlConnectionPool& pool,ILogger& logger);
	uint64_t  create(uint64_t violationId)override;
	void UpdateStatus(uint64_t jobid,ns::AIJobStatus status) override;
	void MakeFailed(uint64_t jobId, const std::string& error) override;
	void IncrementRetry(uint64_t jobid) override;
	std::vector<AIJobDto>GetPendingJobs() override;
};