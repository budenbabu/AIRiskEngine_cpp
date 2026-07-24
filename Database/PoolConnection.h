#pragma once
#include <pqxx\pqxx>
#include <memory>
#include "PostgreSqlConnectionPool.h"


class PostgreSqlConnectionPool;

class PooledConnection{
    PostgreSqlConnectionPool* m_pooll{};
    std::unique_ptr<pqxx::connection> m_connection;
public:
    PooledConnection(PostgreSqlConnectionPool& pool,std::unique_ptr<pqxx::connection> conn);
    ~PooledConnection();
    PooledConnection(const PooledConnection&)=delete;
    PooledConnection& operator=(const PooledConnection&)=delete;
    PooledConnection(PooledConnection&& other) noexcept;
    PooledConnection& operator=(PooledConnection&& other)noexcept;
    pqxx::connection& get();
    pqxx::connection* operator->();
    pqxx::connection& operator*();
    explicit operator bool()const;
};