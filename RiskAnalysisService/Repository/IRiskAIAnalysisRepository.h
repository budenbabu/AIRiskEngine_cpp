#pragma once


#include <iostream>
#include <optional>
#include "../RiskAIAnalysis.h"

class IRiskAIAnalysisRepository {
public:
	virtual ~IRiskAIAnalysisRepository() = default;
	virtual bool Add(const RiskAIAnalysisEntity&) = 0;
	virtual std::optional<RiskAIAnalysisEntity> GetByViolationID(std::uint64_t)const = 0;
	virtual std::optional<RiskAIAnalysisEntity> GetByAnalysisID(std::uint64_t)const = 0;
	virtual std::vector<RiskAIAnalysisEntity> GetAll()const = 0;
	virtual bool Delete(std::uint64_t analysisId) = 0;
};