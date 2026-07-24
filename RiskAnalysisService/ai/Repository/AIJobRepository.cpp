#include "AIJobRepository.h"

AIJobRepository::AIJobRepository(PostgreSqlConnectionPool& pool, ILogger& logger):m_logger(logger),m_pool(pool){}

uint64_t AIJobRepository::create(uint64_t violationId)
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::work tx(*conn);
		auto rows = tx.exec_prepared("ai_job_create", violationId);
		tx.commit();
		if (rows.empty()) {
			m_logger.Error(std::format("Error to create AI job {}", violationId));
			return 0;
		}
		return rows[0]["job_id"].as<uint64_t>();
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("AIJobRepository::create Exception: {}", ex.what()));
		return 0;
	}
}

void AIJobRepository::UpdateStatus(uint64_t jobid, ns::AIJobStatus status)
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::work tx(*conn);
		auto rows = tx.exec_prepared("ai_job_update", ns::ToString(status),jobid);
		tx.commit();
		if (rows.affected_rows()>0) {
			m_logger.Error(std::format("Error to update A job {}", jobid));
		}
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("AIJobRepository::UpdateStatus Exception: {}", ex.what()));
	}
}

void AIJobRepository::MakeFailed(uint64_t jobId, const std::string& error)
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::work tx(*conn);
		auto rows = tx.exec_prepared("ai_job_failed",error,jobId);
		tx.commit();
		if (rows.affected_rows() > 0) {
			m_logger.Error(std::format("Error to update A job {}", jobId));
		}
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("AIJobRepository::MakeFailed Exception: {}", ex.what()));
	}
}

void AIJobRepository::IncrementRetry(uint64_t jobid)
{
	try {
		auto conn = m_pool.Acquire();
		pqxx::work tx(*conn);
		auto rows = tx.exec_prepared("ai_job_retry_count", jobid);
		tx.commit();
		if (rows.affected_rows() > 0) {
			m_logger.Error(std::format("Error to update A job {}", jobid));
		}
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("AIJobRepository::IncrementRetry Exception: {}", ex.what()));
	}
}

std::vector<AIJobDto> AIJobRepository::GetPendingJobs()
{
	try {
		std::vector<AIJobDto> results;
		auto conn = m_pool.Acquire();
		pqxx::read_transaction tx(*conn);
		auto rows = tx.exec(R"(SELECT job_id,violation_id,status,retry_count,COALESCE(error_message,'') FROM ai_job WHERE status IN ('PENDING','PROCESSING') ORDER BY job_id)");
		for (const auto& row : rows) {
			results.push_back({
				.jobID=row["job_id"].as<uint16_t>(),
				.violationId=row["status"].as<uint64_t>(),
				.status=row["status"].as<std::string>(),
				.retryCount=row["retry_count"].as<int>(),
				.errorMsg=row["error_message"].as<std::string>()
			});
		}
		return results;
	}
	catch (const std::exception& ex) {
		m_logger.Error(std::format("AIJobRepository::IncrementRetry Exception: {}", ex.what()));
		return {};
	}
}
