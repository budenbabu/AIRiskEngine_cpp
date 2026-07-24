#pragma once
#include "PostgreSqlConnectionPool.h"

class DatabaseInitializer{
    PostgreSqlConnectionPool& m_connection;
    ILogger& m_logger;
public:
    DatabaseInitializer(PostgreSqlConnectionPool& connection,ILogger& logger);
    void Initialize();
};