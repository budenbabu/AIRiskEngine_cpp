#include "AIJobRepository.h"

AIJobRepository::AIJobRepository(PostgreSqlConnectionPool &pool, ILogger &logger):m_pool(pool),m_logger(logger){}

uint64_t AIJobRepository::Create(uint64_t violationId)
{   
    try{ 
        m_logger.Info(std::format("Created: {}",violationId));
        auto conn=m_pool.Acquire();
        pqxx::work tx(*conn);
        auto rows=tx.exec_prepared("ai_job_create",violationId);        
        tx.commit();
        if(rows.empty()){
            m_logger.Error(std::format("error to create AI job  {}",violationId));
            return 0;
        }
        return rows[0]["job_id"].as<uint64_t>();
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIJobRepository::Create ex: {}",ex.what()));
        return 0;
    }
}

void AIJobRepository::updateStatus(uint64_t jobid, ns::AIJobStatus status)
{
    try{ 
        auto str=std::move(ns::ToString(status));
        m_logger.Info(std::format("updates: {} {}",jobid,str));
        auto conn=m_pool.Acquire();
        pqxx::work tx(*conn);
        auto rows=tx.exec_prepared("ai_job_update_status",str,jobid);        
        tx.commit();
        if(rows.affected_rows()>0){
            m_logger.Error(std::format("error to update AI job  {} {}",jobid,str));
            return;            
        }        
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIJobRepository::updateStatus ex: {}",ex.what()));        
    }
    
}

void AIJobRepository::IncrementRetry(uint64_t jobid)
{
    try{         
        m_logger.Info(std::format("IncrementRetry: {}",jobid));
        auto conn=m_pool.Acquire();
        pqxx::work tx(*conn);
        auto rows=tx.exec_prepared("ai_job_retry_count",jobid);        
        tx.commit();
        if(rows.affected_rows()>0){
            m_logger.Error(std::format("error to IncrementRetry AI job {}",jobid));
            return;            
        }        
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIJobRepository::IncrementRetry ex: {}",ex.what()));        
    }
    
}

void AIJobRepository::MakeFailed(uint64_t jobid,const std::string &error)
{
    try{         
        m_logger.Info(std::format("MakeFailed: {} {}",jobid,error));
        auto conn=m_pool.Acquire();
        pqxx::work tx(*conn);
        auto rows=tx.exec_prepared("ai_job_failed",error,jobid);        
        tx.commit();
        if(rows.affected_rows()>0){
            m_logger.Error(std::format("error to update  AI job {} {}",jobid,error));
            return;            
        }        
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIJobRepository::MakeFailed ex: {}",ex.what()));        
    }
}

std::vector<ns::AIJob> AIJobRepository::GetPendingJobs()
{
    try{         
        std::vector<ns::AIJob> jobs;        
        auto conn=m_pool.Acquire();
        pqxx::read_transaction tx(*conn);
        auto rows=tx.exec(R"(SELECT job_id,violation_id,status,retry_count,COALESCE(error_message,'') 
            FROM ai_job WHERE status IN ('PENDING','PROCESSING') ORDER BY job_id)");         
        if(rows.empty()){
            m_logger.Error("No pending or processing AI jobs found");
            return {};            
        }        
        jobs.reserve(rows.size());
        for(const auto& row : rows){
            jobs.push_back({
                .jobID=row["job_id"].as<uint64_t>(),
                .violationId=row["violation_id"].as<uint64_t>(),
                .status=ns::FromString(row["status"].as<std::string>()),
                .retryCount=row["retry_count"].as<int>(),
                .errorMsg=row["coalesce"].as<std::string>()
            });
        }
        return jobs;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("AIJobRepository::IncrementRetry ex: {}",ex.what()));        
        return {};
    }
    
}
