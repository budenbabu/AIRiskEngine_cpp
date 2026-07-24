#include "PostgreSqlConnectionPool.h"

void PostgreSqlConnectionPool::RegiterStatement(pqxx::connection &conn)
{
   try{
	    conn.prepare("insert_trade",R"(INSERT INTO trades (symbol,side,quantity,price) VALUES($1,$2,$3,$4))");

	    conn.prepare("trade_exists",R"(SELECT 1 FROM trades WHERE trade_id=$1)");

	    conn.prepare("get_trade_by_id", R"(SELECT trade_id,symbol,side,quantity,price,timestamp FROM trades WHERE trade_id=$1)");

	    conn.prepare("get_trade_by_symbol",R"(SELECT trade_id,symbol,side,quantity,price,timestamp FROM trades WHERE symbol=$1 ORDER BY trade_id)");

	    //
	    // Position
	    //

	    conn.prepare("get_position_by_symbol",R"(SELECT symbol,quantity,avg_price,market_price,realized_pnl FROM positions WHERE symbol=$1)");
        conn.prepare("get_position_for_update",R"(SELECT symbol,quantity,avg_price,market_price,realized_pnl FROM positions WHERE symbol=$1 FOR UPDATE)");

	    conn.prepare("upsert_position",
		       R"(INSERT INTO positions(symbol,quantity,avg_price,market_price,realized_pnl) VALUES($1,$2,$3,$4,$5) ON CONFLICT(symbol)
                DO UPDATE SET quantity=EXCLUDED.quantity,
                 avg_price=EXCLUDED.avg_price,
                 market_price=EXCLUDED.market_price,
                 realized_pnl=EXCLUDED.realized_pnl)");

	    conn.prepare("delete_position",R"(DELETE FROM positions WHERE symbol=$1)");
        conn.prepare("update_market_price","UPDATE positions SET market_price = $1 WHERE symbol = $2");

        //Risk rule
        conn.prepare("insert_risk_rule", R"(INSERT INTO risk_rules (rule_type,symbol,rule_value,enabled,description) VALUES($1,$2,$3,$4,$5))");

        conn.prepare("update_risk_rule",R"(UPDATE risk_rules SET rule_type=$1,symbol=$2,rule_value=$3,enabled=$4,description=$5 WHERE rule_id=$6)");

        conn.prepare("delete_risk_rule",R"(DELETE FROM risk_rules WHERE rule_id=$1)");

        //Risk Violation
        conn.prepare("insert_risk_violation",R"(
            INSERT INTO risk_violations(timestamp,symbol,violation_type,message,trade_json) VALUES($1,$2,$3,$4,$5) RETURNING violation_id
        )");

        //Risk AI Analysis risk_ai_analysis
        conn.prepare("insert_risk_ai",R"(INSERT INTO risk_ai_analysis(violation_id,analysis,recommendation,model_name,confidence,severity) VALUES ($1,$2,$3,$4,$5,$6))");

        conn.prepare("get_risk_ai_vid",R"(SELECT * FROM risk_ai_analysis WHERE violation_id=$1)");

        conn.prepare("get_risk_ai_by_id",R"(SELECT * FROM risk_ai_analysis WHERE analysis_id=$1)");
        conn.prepare("get_all_risk_ai",R"(SELECT * FROM risk_ai_analysis ORDER BY created_at DESC)");
        conn.prepare("delete_risk_ai",R"(DELETE FROM risk_ai_analysis WHERE analysis_id=$1)");

        // AI job status
        conn.prepare("ai_job_create", R"(INSERT INTO ai_job(violation_id,status) VALUES($1,'PENDING') RETURNING job_id)");
        conn.prepare("ai_job_update_status", R"(
            UPDATE ai_job SET 
                    status = $1::varchar(20),
                    started_at = CASE
                        WHEN $1::varchar(20) = 'PROCESSING' THEN NOW()
                        ELSE started_at
                    END,
                    completed_at = CASE
                        WHEN $1::varchar(20) IN ('COMPLETED', 'FAILED') THEN NOW()
                        WHEN $1::varchar(20) = 'PROCESSING' THEN NULL
                        ELSE completed_at
                    END
                WHERE job_id = $2::bigint;)");
        conn.prepare("ai_job_failed", R"(UPDATE ai_job SET status='FAILED', completed_at=NOW(),error_message=$1 WHERE job_id=$2)");
        conn.prepare("ai_job_retry_count", R"(UPDATE ai_job SET retry_count = retry_count + 1 WHERE job_id=$1)");
        
        
        
   }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgreSqlConnection::RegisterStatements ex: {}",ex.what()));
   }
}

PostgreSqlConnectionPool::PostgreSqlConnectionPool(DataBaseConfig& config,ILogger& logger) : 
    m_semaphore(static_cast<std::ptrdiff_t>(config.m_poolsize)), m_logger(logger),
    m_conStr(std::format("host={} port={} dbname={} user={} password={}",config.m_host, config.m_port, config.m_database, config.m_user, config.m_password))
{
    
    for(std::size_t i=0;i<config.m_poolsize;++i){
        auto conn=std::make_unique<pqxx::connection>(m_conStr);
        RegiterStatement(*conn);
        m_connections.push(std::move(conn));
    }
    m_logger.Info(std::format("Connection pool ready to uses size: {}",config.m_poolsize));
}

PooledConnection PostgreSqlConnectionPool::Acquire()
{
    m_semaphore.acquire();
    ++m_totalAcquired;
    std::lock_guard<std::mutex> lock(mtx);
    auto conn=std::move(m_connections.front());
    m_connections.pop();    
    return {*this,std::move(conn)};
}

void PostgreSqlConnectionPool::Release(ConnectionPtr conn)
{
    std::lock_guard lock(mtx);
    if(!conn->is_open()){
        conn=std::make_unique<pqxx::connection>(m_conStr);
        RegiterStatement(*conn);
    }else{
        m_connections.push(std::move(conn));        
    }
    m_semaphore.release();
    ++m_totalReleased;
}

std::size_t PostgreSqlConnectionPool::Avialable() const
{
    std::lock_guard lock(mtx);    
    return m_connections.size();
}
