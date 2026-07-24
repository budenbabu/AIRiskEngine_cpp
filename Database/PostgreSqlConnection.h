#pragma once

#include <pqxx\pqxx>
#include <format>
#include "DatabaseConfig.h"
#include "../Loogger/ILogger.h"

class PostgreSqlConnection{
    pqxx::connection m_connection;
    ILogger& m_logger;
    void RegisterStatements();
public:
    explicit PostgreSqlConnection(const DataBaseConfig& config,ILogger& logger);
    pqxx::connection& GetConnection();
    void closeConnection();
};