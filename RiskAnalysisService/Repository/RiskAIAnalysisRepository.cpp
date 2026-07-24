#include "RiskAIAnalysisRepository.h"

RiskAIAnalysisRepository::RiskAIAnalysisRepository(PostgreSqlConnectionPool& pool,ILogger& logger):m_pool(pool),m_logger(logger){}

bool RiskAIAnalysisRepository::Add(const RiskAIAnalysisEntity& entity)
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::work tx(*conn);
		tx.exec_prepared("insert_risk_ai", entity.violationId, entity.analysis, entity.recommendation, entity.modelName, entity.confidence,entity.severity);
		tx.commit();
		return true;
	}catch(const std::exception& ex){
		auto estr = std::move(std::format("RiskAIAnalysisRepository::Add Exception: {}", ex.what()));
		m_logger.Error(estr);	
		throw std::runtime_error(estr);
		return false;
	}
	
}

std::optional<RiskAIAnalysisEntity> RiskAIAnalysisRepository::GetByViolationID(std::uint64_t id) const
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::read_transaction tx(*conn);
		auto rows=tx.exec_prepared("get_risk_ai_vid", id);		
		if (rows.empty()) return std::nullopt;
		auto row = rows[0];
		return RiskAIAnalysisEntity{
			.analysisId = row["analysis_id"].as<std::uint64_t>(),
			.violationId = row["violation_id"].as<std::uint64_t>(),
			.analysis = row["analysis"].as<std::string>(),
			.recommendation = row["recommendation"].is_null()?"":row["recommendation"].as<std::string>(),
			.modelName = row["model_name"].is_null()?"":row["model_name"].as<std::string>(),
			.confidence = row["confidence"].is_null()?0.0:row["confidence"].as<double>(),
			.severity=row["severity"].is_null()?0.0:row["severity"].as<double>(),
			.createdAt = row["created_at"].as<std::string>()
		};
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("RiskAIAnalysisRepository::GetByViolationID Exception: {}", ex.what()));
		return std::nullopt;
	}
}

std::optional<RiskAIAnalysisEntity> RiskAIAnalysisRepository::GetByAnalysisID(std::uint64_t id) const
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::read_transaction tx(*conn);
		auto rows = tx.exec_prepared("get_risk_ai_by_id", id);
		if (rows.empty()) return std::nullopt;
		auto row = rows[0];
		return RiskAIAnalysisEntity{
			.analysisId = row["analysis_id"].as<std::uint64_t>(),
			.violationId = row["violation_id"].as<std::uint64_t>(),
			.analysis = row["analysis"].as<std::string>(),
			.recommendation = row["recommendation"].is_null() ? "" : row["recommendation"].as<std::string>(),
			.modelName = row["model_name"].is_null() ? "" : row["model_name"].as<std::string>(),
			.confidence = row["confidence"].is_null() ? 0.0 : row["confidence"].as<double>(),
			.severity=row["severity"].is_null()?0.0:row["severity"].as<double>(),
			.createdAt = row["created_at"].as<std::string>()
		};
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("RiskAIAnalysisRepository::GetByAnalysisID Exception: {}", ex.what()));
		return std::nullopt;
	}
}

std::vector<RiskAIAnalysisEntity> RiskAIAnalysisRepository::GetAll() const
{
	try {
		std::vector<RiskAIAnalysisEntity> results;
		auto conn = m_pool.Acquire();
		pqxx::read_transaction tx(*conn);
		auto rows = tx.exec_prepared("get_all_risk_ai");
		
		for(auto row : rows)
		 results.push_back(
			{
				.analysisId = row["analysis_id"].as<std::uint64_t>(),
				.violationId = row["violation_id"].as<std::uint64_t>(),
				.analysis = row["analysis"].as<std::string>(),
				.recommendation = row["recommendation"].is_null() ? "" : row["recommendation"].as<std::string>(),
				.modelName = row["model_name"].is_null() ? "" : row["model_name"].as<std::string>(),
				.confidence = row["confidence"].is_null() ? 0.0 : row["confidence"].as<double>(),
				.severity=row["severity"].is_null()?0.0:row["severity"].as<double>(),
				.createdAt = row["created_at"].as<std::string>()
				
			});
		return results;
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("RiskAIAnalysisRepository::GetAll Exception: {}", ex.what()));
		return {};
	}
}

bool RiskAIAnalysisRepository::Delete(std::uint64_t analysisId)
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::work tx(*conn);
		tx.exec_prepared("delete_risk_ai", analysisId);
		tx.commit();
		return true;
	}catch (const std::exception& ex) {
		m_logger.Error(std::format("RiskAIAnalysisRepository::GetAll Exception: {}",ex.what()));
		return false;
	}
}
