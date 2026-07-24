#pragma once
#include <iostream>
#include "../RiskAIAnalysis.h"

class IAIJobRepository{
    public:
    virtual ~IAIJobRepository()=default;
    virtual uint64_t Create(uint64_t violationId)=0;
    virtual void updateStatus(uint64_t jobid,ns::AIJobStatus status)=0;
    virtual void IncrementRetry(uint64_t jobid)=0;
    virtual void MakeFailed(uint64_t jobid,const std::string& error)=0;
    virtual std::vector<ns::AIJob> GetPendingJobs()=0;
};