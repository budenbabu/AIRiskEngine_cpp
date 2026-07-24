#pragma once


#include <format>
#include "IRiskAIAnalysisRepository.h"
#include "../../Database/PostgreSqlConnectionPool.h"
#include "../../Loogger/ILogger.h"

class RiskAIAnalysisRepository : public IRiskAIAnalysisRepository {
	PostgreSqlConnectionPool& m_pool;
	ILogger& m_logger;
public:
	explicit RiskAIAnalysisRepository(PostgreSqlConnectionPool& pool,ILogger& logger);
	

	// Inherited via IRiskAIAnalysisRepository
	bool Add(const RiskAIAnalysisEntity&) override;

	std::optional<RiskAIAnalysisEntity> GetByViolationID(std::uint64_t) const override;

	std::optional<RiskAIAnalysisEntity> GetByAnalysisID(std::uint64_t) const override;

	std::vector<RiskAIAnalysisEntity> GetAll() const override;

	bool Delete(std::uint64_t analysisId) override;

};
