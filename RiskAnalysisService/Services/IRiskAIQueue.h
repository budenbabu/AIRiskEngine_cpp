#pragma once

#include <iostream>
#include "../RiskAIAnalysis.h"

class IRiskAIQueue {
public:
	virtual ~IRiskAIQueue() = default;
	virtual void Enqueue(uint64_t violationId) = 0;	
	virtual void Enqueue(const AIQueueItem& item)=0;	
	virtual void RecoverPendingJobs()=0;
};
