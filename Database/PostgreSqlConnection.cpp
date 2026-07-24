#include "PostgreSqlConnection.h"

void PostgreSqlConnection::RegisterStatements()
{
    auto& conn = m_connection;
    //
    // Trade
    //
    try{
    conn.prepare(
        "insert_trade",
        R"(
            INSERT INTO trades
            (
                trade_id,
                symbol,
                side,
                quantity,
                price                
            )
            VALUES
            (
                $1,$2,$3,$4,$5
            )
        )");

    conn.prepare(
        "trade_exists",
        R"(
            SELECT 1
            FROM trades
            WHERE trade_id=$1
        )");

    conn.prepare(
        "get_trade_by_id",
        R"(
            SELECT
                trade_id,
                symbol,
                side,
                quantity,
                price,
                timestamp
            FROM trades
            WHERE trade_id=$1
        )");

    conn.prepare(
        "get_trade_by_symbol",
        R"(
            SELECT
                trade_id,
                symbol,
                side,
                quantity,
                price,
                timestamp
            FROM trades
            WHERE symbol=$1
            ORDER BY trade_id
        )");

    //
    // Position
    //

    conn.prepare(
        "get_position_by_symbol",
        R"(
            SELECT
                symbol,
                quantity,
                avg_price,
                market_price,
                realized_pnl
            FROM positions
            WHERE symbol=$1
        )");

    conn.prepare(
        "upsert_position",
        R"(
            INSERT INTO positions
            (
                symbol,
                quantity,
                avg_price,
                market_price,
                realized_pnl
            )
            VALUES
            (
                $1,$2,$3,$4,$5
            )
            ON CONFLICT(symbol)
            DO UPDATE SET
                quantity=
                    EXCLUDED.quantity,

                avg_price=
                    EXCLUDED.avg_price,

                market_price=
                    EXCLUDED.market_price,

                realized_pnl=
                    EXCLUDED.realized_pnl
        )");        

        conn.prepare(
            "delete_position",
            R"(
                DELETE
                FROM positions
                WHERE symbol=$1
            )");
        conn.prepare("update_market_price","UPDATE positions SET market_price = $1 WHERE symbol = $2");
        }catch(const std::exception& ex){
            m_logger.Error(std::format("PostgreSqlConnection::RegisterStatements ex: {}",ex.what()));
        }
}

PostgreSqlConnection::PostgreSqlConnection(const DataBaseConfig &config, ILogger &logger) : m_logger(logger),
    m_connection(std::format("host={} port={} dbname={} user={} password={}",config.m_host, config.m_port, config.m_database, config.m_user, config.m_password))
{
    try{
        if(!m_connection.is_open()){
            m_logger.Error("unable to open connection");
            return;
        }
        RegisterStatements();
        pqxx::work tx(m_connection);
        auto result=tx.exec("select version()");
        m_logger.Info(std::format("result: {}",result[0][0].c_str()));
        tx.commit();

    }catch(const std::exception& ex){
        m_logger.Error(std::format("Exception: {}",ex.what()));
    }
}

pqxx::connection &PostgreSqlConnection::GetConnection()
{
    return m_connection;
}

