#pragma once
#include <iostream>
#include "../../RiskAIAnalysis.h"

class IAIJobRepository {
public:
	virtual ~IAIJobRepository() = default;
	virtual uint64_t  create(uint64_t violationId) = 0;
	virtual void UpdateStatus(uint64_t jobid, ns::AIJobStatus status) = 0;
	virtual void MakeFailed(uint64_t jobId, const std::string& error) = 0;
	virtual void IncrementRetry(uint64_t jobid) = 0;
	virtual std::vector<AIJobDto> GetPendingJobs() = 0;
};