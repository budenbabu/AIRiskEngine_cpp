#include "AIAnalysisRepository.h"

AIAnalysisRepository::AIAnalysisRepository(PostgreSqlConnectionPool &pool, ILogger &logger):m_pool(pool),m_logger(logger){}

void AIAnalysisRepository::Save(const ns::AIAnalysis& analysis)
{
    try{
        auto conn=m_pool.Acquire();
        if (!conn) {
            m_logger.Error(std::format("Failed to acquire DB connection for jobId: {}", analysis.jobId));
            return;
        }
        pqxx::work tx(*conn);
        auto rows= tx.exec_prepared("insert_ai_analysis",analysis.jobId,analysis.violationId,analysis.modelName,analysis.analysisJson,analysis.processingTimeMs);
        tx.commit();
        if(rows.affected_rows()==0){
            m_logger.Error(std::format("Error to insert ai analysis {} {}",analysis.jobId,analysis.violationId));
        }
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIAnalysisRepository::Save ex: {}",ex.what()));
    }
}

std::optional<ns::AIAnalysis> AIAnalysisRepository::GetByJobId(uint64_t jobId)
{
    try{
         auto conn=m_pool.Acquire();
        if (!conn) {
            m_logger.Error(std::format("Failed to acquire DB connection for jobId: {}", jobId));
            return std::nullopt;
        }
        pqxx::nontransaction tx(*conn);
        auto rows=tx.exec_params("select analysis_id,job_id,violation_id,model_name,analysis,processing_time_ms,created_at from ai_analysis where job_id=$1;",jobId);
        if(rows.empty()){
            m_logger.Error(std::format("Error to find the job_d ai analysis {}",jobId));
            return std::nullopt;
        }
        const auto& row=rows[0];
        return ns::AIAnalysis{
            .analysisId=row["analysis_id"].as<uint64_t>(),
            .jobId=row["job_id"].as<uint64_t>(),
            .violationId=row["violation_id"].as<uint64_t>(),
            .modelName=row["model_name"].as<std::string>(),
            .analysisJson=row["analysis"].as<std::string>(),
            .processingTimeMs=row["processing_time_ms"].as<uint64_t>(),
            .createdAt=row["created_at"].as<std::string>()            
        };
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIAnalysisRepository::GetByJobId ex: {}",ex.what()));
        return std::nullopt;
    }
}

std::vector<ns::AIAnalysis> AIAnalysisRepository::GetByViolationId(uint64_t vid)
{
    try{
         auto conn=m_pool.Acquire();
        if (!conn) {
            m_logger.Error(std::format("Failed to acquire DB connection for vid: {}", vid));
            return {};
        }
        pqxx::nontransaction tx(*conn);
        auto rows=tx.exec_params("select analysis_id,job_id,violation_id,model_name,analysis,processing_time_ms,created_at from ai_analysis where violation_id=$1;",vid);
        if(rows.empty()){
            m_logger.Error(std::format("no records to find the vid ai analysis {}",vid));
            return {};
        }
        std::vector<ns::AIAnalysis> results;
        results.reserve(rows.size());
        for(const auto& row: rows)
            results.push_back(ns::AIAnalysis{
                .analysisId=row["analysis_id"].as<uint64_t>(),
                .jobId=row["job_id"].as<uint64_t>(),
                .violationId=row["violation_id"].as<uint64_t>(),
                .modelName=row["model_name"].as<std::string>(),
                .analysisJson=row["analysis"].as<std::string>(),
                .processingTimeMs=row["processing_time_ms"].as<uint64_t>(),
                .createdAt=row["created_at"].as<std::string>()            
            });        
        return results;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIAnalysisRepository::GetByJobId ex: {}",ex.what()));
        return {};
    }
}
