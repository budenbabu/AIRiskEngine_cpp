#include "PoolConnection.h"


PooledConnection::PooledConnection(PostgreSqlConnectionPool& pool,std::unique_ptr<pqxx::connection> conn)
    :m_pooll(&pool),m_connection(std::move(conn)){}

PooledConnection::~PooledConnection()
{
    if(m_pooll && m_connection)
        m_pooll->Release(std::move(m_connection));
}

PooledConnection::PooledConnection(PooledConnection &&other) noexcept:
    m_pooll(other.m_pooll),m_connection(std::move(other.m_connection))
{
    other.m_pooll=nullptr;
}

PooledConnection& PooledConnection::operator=(PooledConnection &&other) noexcept
{
    if(this==&other) return *this;

    if(m_pooll && m_connection) 
        m_pooll->Release(std::move(m_connection));
    m_pooll=other.m_pooll;
    m_connection=std::move(other.m_connection);
    other.m_pooll=nullptr;
    return *this;
}

pqxx::connection &PooledConnection::get(){ return *m_connection; }

pqxx::connection *PooledConnection::operator->(){ return m_connection.get(); }

pqxx::connection &PooledConnection::operator*(){ return *m_connection; }

PooledConnection::operator bool() const{ return m_connection!=nullptr; }
