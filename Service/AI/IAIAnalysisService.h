#pragma once

#include <iostream>
#include <optional>
#include "../../RiskAnalysisService/RiskAIAnalysis.h"


class IAIAnalysisService{
public:
    virtual ~IAIAnalysisService()=default;
    virtual std::optional<RiskAIAnalysisEntity> getByViolationID(uint64_t vid)=0;
    virtual std::optional<RiskAIAnalysisEntity> GetByAnalysisID(uint64_t aid)=0;
    virtual std::vector<RiskAIAnalysisEntity> GetAll()=0;
};