#pragma once
#include <pqxx\pqxx>
#include <string>
#include <queue>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <semaphore>
#include <format>
#include "PoolConnection.h"
#include "../Loogger/ILogger.h"
#include "DatabaseConfig.h"

class PooledConnection;

class PostgreSqlConnectionPool{
    
    using ConnectionPtr= std::unique_ptr<pqxx::connection>;
    std::queue<ConnectionPtr> m_connections;    
    std::string m_conStr;
    mutable std::mutex mtx;    
    std::counting_semaphore<> m_semaphore;
    ILogger& m_logger;
    std::atomic<std::uint64_t> m_totalAcquired{0};
    std::atomic<std::uint64_t> m_totalReleased{0};
    void RegiterStatement(pqxx::connection& conn);
public:
    PostgreSqlConnectionPool(DataBaseConfig& config,ILogger& looger);
    ~PostgreSqlConnectionPool(){
        
        m_logger.Info(std::format("Available: {}",Avialable() ));  
        m_logger.Info(std::format("Acquired:  {}",m_totalAcquired.load())); 
        m_logger.Info(std::format("Releasesd: {}",m_totalReleased.load()));
    };
    PostgreSqlConnectionPool(const PostgreSqlConnectionPool&)=delete;
    PostgreSqlConnectionPool operator=(const PostgreSqlConnectionPool&)=delete;

    PooledConnection Acquire();
    void Release(ConnectionPtr conn);
    std::size_t Avialable()const;



};