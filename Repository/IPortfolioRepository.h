#pragma once
#include <pqxx\pqxx>
#include <vector>
#include "..\Models\Position.h"


class IPortfolioRepository
{
public:

    virtual ~IPortfolioRepository() = default;

    virtual std::vector<ns::Position>  GePositions() const = 0;

    virtual std::optional<ns::Position>  GetBySymbol(const std::string& symbol) const = 0;

    virtual bool Add(const ns::Position& position) = 0;

    virtual bool Update(const ns::Position& position) = 0;

    virtual bool Remove(const std::string& symbol) = 0;

    virtual bool UpdateMarketPrice(const std::string& symbol,double marketPrice) = 0;
    
    virtual bool Upsert(pqxx::transaction_base& tx,const ns::Position& position)=0;
    virtual std::optional<ns::Position>  GetBySymbol(pqxx::transaction_base& tx,const std::string& symbol) const = 0;
    virtual bool Remove(pqxx::transaction_base& tx,const std::string& symbol) = 0;
    virtual std::optional<ns::Position> GetBySymbolForUpdate(pqxx::transaction_base& tx,const std::string& symbol) = 0;


};