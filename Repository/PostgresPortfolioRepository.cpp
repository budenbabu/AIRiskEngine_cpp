#include "PostgresPortfolioRepository.h"

PostgresPortfolioRepository::PostgresPortfolioRepository(PostgreSqlConnectionPool &db,ILogger& logger):m_db(db),m_logger(logger){}

std::vector<ns::Position> PostgresPortfolioRepository::GePositions() const
{
    try{
        auto conn=m_db.Acquire();
        pqxx::read_transaction tx(*conn);
        const auto& rows=tx.exec(R"(select symbol,quantity,avg_price,market_price,realized_pnl from positions;)");
        std::vector<ns::Position> postions;
        postions.reserve(rows.size());
        for(const auto& row : rows)
            postions.push_back(PostgresPortfolioRepository::MapPostion(row));
        return postions;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresPortfolioRepository::GePositions Exception: {}",ex.what()));        
        return {};          
    }
}

std::optional<ns::Position> PostgresPortfolioRepository::GetBySymbol(const std::string &symbol) const
{
    try{
        auto conn=m_db.Acquire();
        pqxx::read_transaction tx(*conn);
        const auto& rows=tx.exec_prepared("get_position_by_symbol",symbol);
        if(rows.empty()){
            m_logger.Error(std::format("PostgresPortfolioRepository::GetBySymbol Symbol not found: {}",symbol));        
            return std::nullopt;
        }
        return PostgresPortfolioRepository::MapPostion(rows[0]);
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresPortfolioRepository::GetBySymbol Exception: {}",ex.what()));        
        return std::nullopt;             
    }
}

bool PostgresPortfolioRepository::Add(const ns::Position &pos)
{
    try{
        auto conn=m_db.Acquire();        
        pqxx::work tx(*conn);        
        const auto& result= tx.exec_prepared("upsert_position",pos.symbol,pos.quantity,pos.averagePrice,pos.marketPrice,pos.realizedPnl);
        if (result.affected_rows() == 0) {
            m_logger.Info(std::format("skipped: add/updated {} in database.",pos.symbol));                    
            return false; 
        }
        tx.commit();
        m_logger.Info(std::format("position record add/update by symbol: {}",pos.symbol));
        return true;
    }catch(const std::exception& ex){        
        m_logger.Error(std::format("PostgresPortfolioRepository::Add Exception: {}",ex.what()));        
        return false;       
    }
}

bool PostgresPortfolioRepository::Update(const ns::Position &position)
{
    Add(position);
    return false;
}

bool PostgresPortfolioRepository::Remove(const std::string &symbol)
{
    //delete_position
    try{
        auto conn=m_db.Acquire();        
        pqxx::work tx(*conn);
        const auto& result= tx.exec_prepared("delete_position",symbol);
        if (result.affected_rows() == 0) {
            m_logger.Info(std::format("Remove skipped: Symbol {} not found in database.", symbol));                        
            return false; 
        }
        tx.commit();
        return true;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresPortfolioRepository::Remove Exception: {}",ex.what()));        
        return false;
    }
}

bool PostgresPortfolioRepository::UpdateMarketPrice(const std::string &symbol, double marketPrice)
{
    try{
        auto conn=m_db.Acquire();        
        pqxx::work tx(*conn);
        const auto& result= tx.exec_prepared("update_market_price",marketPrice,symbol);
        if(result.affected_rows()==0) return false;
        tx.commit();
        return true;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresPortfolioRepository::UpdateMarketPrice Exception: {}",ex.what()));        
        return false;        
    }
    
}

bool PostgresPortfolioRepository::Upsert(pqxx::transaction_base &tx, const ns::Position &pos)
{
    try{
        m_logger.Info(std::format("Upsert: symbol: {} {}",pos.symbol,pos.symbol.size()));
        tx.exec_prepared("upsert_position",pos.symbol,pos.quantity,pos.averagePrice,pos.marketPrice,pos.realizedPnl);
        return true;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresPortfolioRepository::Upsert Exception: {}",ex.what()));        
        return false;        
    }
}

std::optional<ns::Position> PostgresPortfolioRepository::GetBySymbol(pqxx::transaction_base &tx, const std::string &symbol) const
{
    try{
        const auto& result=tx.exec_prepared("get_position_by_symbol",symbol);
        if(result.empty()) return std::nullopt;    
        return MapPostion(result[0]);
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresPortfolioRepository::GetBySymbol tx Exception: {}",ex.what()));        
        return std::nullopt;
    }
}

bool PostgresPortfolioRepository::Remove(pqxx::transaction_base &tx, const std::string &symbol)
{
    try{
         tx.exec_prepared("delete_position",symbol);
         return true;
    }catch(const std::exception& ex){
        m_logger.Error(std::format("PostgresPortfolioRepository::Remove tx Exception: {}",ex.what()));        
        return false;
    }   
}

std::optional<ns::Position> PostgresPortfolioRepository::GetBySymbolForUpdate(pqxx::transaction_base &tx, const std::string &symbol)
{
    try{
        auto result=tx.exec_prepared("get_position_for_update",symbol);
        if(result.empty()) return std::nullopt;
        const auto& row=result[0];
        return MapPostion(row);
    }catch(const std::exception ex){
         m_logger.Error(std::format("PostgresPortfolioRepository::GetBySymbolForUpdate Exception: {}",ex.what()));        
        return std::nullopt;   
    }
    
}
