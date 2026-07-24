#pragma once

#include <boost\core\ignore_unused.hpp>
#include <memory>
#include <format>
#include "IRiskAIQueue.h"
#include "../ai/AIExecutor.h"
#include "IRiskAIAnalysisService.h"
#include "../../Loogger/ILogger.h"
#include "../Repository/IAIJobRepository.h"


class RiskAIQueue :public IRiskAIQueue {
	std::shared_ptr<AIExecutor> m_executor;
	IRiskAIAnalysisService& m_service;	
	IAIJobRepository& m_repo;
	ILogger& m_logger;
public:
	RiskAIQueue(std::shared_ptr<AIExecutor> executor, IRiskAIAnalysisService& service,IAIJobRepository& repo,ILogger& logger);
	void Enqueue(uint64_t violationId)override;
	void Enqueue(const AIQueueItem& item)override;
	void Process(const AIQueueItem& item);	
	void RecoverPendingJobs()override;
	//uint64_t Create(uint64_t violationId)override;

};