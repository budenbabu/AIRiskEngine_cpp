#pragma once
#include <iostream>
#include <vector>

#include "../RiskAIAnalysis.h"

class IAIAnalysisRepository{
public:
    virtual ~IAIAnalysisRepository()=default;
    virtual void Save(const ns::AIAnalysis& analysis)=0;
    virtual std::optional<ns::AIAnalysis> GetByJobId(uint64_t jobId)=0;
    virtual std::vector<ns::AIAnalysis> GetByViolationId(uint64_t vid)=0;
};