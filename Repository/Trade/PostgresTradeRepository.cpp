#include "PostgresTradeRepository.h"

PostgresTradeRepository::PostgresTradeRepository(PostgreSqlConnectionPool &db, ILogger &logger) : m_db(db), m_logger(logger) {}

bool PostgresTradeRepository::Add(const ns::Trade &trade)
{
    try{
        auto conn=m_db.Acquire();
        pqxx::work tx(*conn);
        tx.exec_params(R"(insert into trades(symbol,side,quantity,price) values($1,$2,$3,$4))",
            trade.symbol,static_cast<int>(trade.side),trade.quantity,trade.price);
        tx.commit();
        return true;
    }catch(const std::exception& ex){
        auto error=std::format("PostgresTradeRepository::Add Exception: {}",ex.what());
        m_logger.Error(error);        
        return false;
    }
}

std::optional<ns::Trade> PostgresTradeRepository::GetById(std::uint64_t tradeId) const
{
    try{
        auto conn=m_db.Acquire();
        pqxx::read_transaction tx(*conn);
        auto result=tx.exec_params(R"(SELECT trade_id,symbol,side,quantity,price,timestamp FROM trades WHERE trade_id = $1)",tradeId);
        if(result.empty()){            
            m_logger.Error(std::format("PostgresTradeRepository::GetById error: {} not found",tradeId));
            return std::nullopt;                    
        }
        return PostgresTradeRepository::MapTrade(result[0]);
    }catch(const std::exception& ex){    
        m_logger.Error(std::format("PostgresTradeRepository::GetById Exception: {}",ex.what()));        
        return std::nullopt;
    }
}

std::vector<ns::Trade> PostgresTradeRepository::GetBySymbol(const std::string &symbol) const
{    
    try{
        auto conn=m_db.Acquire();
        pqxx::read_transaction tx(*conn);
        auto result=tx.exec_params(R"(SELECT trade_id,symbol,side,quantity,price,timestamp FROM trades WHERE symbol = $1)",symbol);
        if(result.empty()){            
            m_logger.Error(std::format("PostgresTradeRepository::GetBySymbol error: {} not found",symbol));
            return {};                    
        }        
        std::vector<ns::Trade> trades;
        trades.reserve(result.size());
        for(const auto& row : result){
            trades.push_back( PostgresTradeRepository::MapTrade(row));
        }
        return trades;
    }catch(const std::exception& ex){    
        m_logger.Error(std::format("PostgresTradeRepository::GetById Exception: {}",ex.what()));                
        return {};
    }    
}

std::vector<ns::Trade> PostgresTradeRepository::GetAll() const
{
    try{
        auto conn=m_db.Acquire();
        pqxx::read_transaction tx(*conn);
        auto result=tx.exec(R"(SELECT trade_id,symbol,side,quantity,price,timestamp FROM trades;)");
        if(result.empty()){            
            m_logger.Error(std::format("PostgresTradeRepository::GetAll error: not found"));
            return {};                    
        }        
        std::vector<ns::Trade> trades;
        trades.reserve(result.size());
        for(const auto& row : result){
            trades.push_back(PostgresTradeRepository::MapTrade(row));
        }
        return trades;
    }catch(const std::exception& ex){    
        m_logger.Error(std::format("PostgresTradeRepository::GetALL Exception: {}",ex.what()));                
        return {};
    }
}

bool PostgresTradeRepository::Exists(std::uint64_t tradeId) const
{
    try{
        auto conn=m_db.Acquire();
        pqxx::read_transaction tx(*conn);
        auto r=tx.exec_params("select 1 from trades where trade_id=$1",tradeId);    
        return !r.empty();

    }catch(const std::exception& ex){    
        m_logger.Error(std::format("PostgresTradeRepository::Exists Exception: {}",ex.what()));        
        return false;
    }
}

bool PostgresTradeRepository::Remove(std::uint64_t tradeId)
{
    boost::ignore_unused(tradeId);
    return false;
}

bool PostgresTradeRepository::Add(pqxx::transaction_base &tx, const ns::Trade &trade)
{
    try{
        const auto& resutl=tx.exec_prepared("insert_trade",trade.symbol,static_cast<int>(trade.side),trade.quantity,trade.price);
        m_logger.Info(std::format("Result: {}",resutl.affected_rows()));
        return true;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresTradeRepository::Add tx Exception: {}",ex.what()));        
        return false;
    }   
}
