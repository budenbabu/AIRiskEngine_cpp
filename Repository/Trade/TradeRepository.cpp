#include "TradeRepository.h"
#include <boost\core\ignore_unused.hpp>

TradeRepository::TradeRepository()
{
}

bool TradeRepository::Add(const ns::Trade &trade)
{    
    std::unique_lock lock(mtx);    
    ns::Trade storedTrade=trade;
    storedTrade.tradeId=m_nextTradeId++;
    auto[it,inserted]=m_TradebyId.emplace(storedTrade.tradeId, storedTrade);
    if(!inserted) return false;
    m_TradebySymbol[storedTrade.symbol].push_back(storedTrade.tradeId);
    return true;
}

std::optional<ns::Trade> TradeRepository::GetById(std::uint64_t tradeId) const
{
    std::shared_lock lock(mtx);
    auto it=m_TradebyId.find(tradeId);
    if(it==m_TradebyId.end()) return std::nullopt;
    return it->second;
}

std::vector<ns::Trade> TradeRepository::GetBySymbol(const std::string &symbol) const
{
    std::vector<ns::Trade> results;
    auto it=m_TradebySymbol.find(symbol);
    if(it==m_TradebySymbol.end()) return results;
    results.reserve(it->second.size());
    for(auto id: it->second) {
        auto trade=m_TradebyId.find(id);
        if(trade!=m_TradebyId.end())
            results.push_back(trade->second);
    }
    return results;
}

std::vector<ns::Trade> TradeRepository::GetAll() const
{
    std::shared_lock lock(mtx);
    std::vector<ns::Trade> results;
    for(const auto& [id,trade] : m_TradebyId)
        results.push_back(trade);
    return results;
}

bool TradeRepository::Exists(std::uint64_t tradeId) const
{   std::shared_lock lock(mtx);    
    return m_TradebyId.find(tradeId) !=m_TradebyId.end();
}

bool TradeRepository::Add(pqxx::transaction_base &tx, const ns::Trade &trade)
{
    boost::ignore_unused(tx);
    boost::ignore_unused(trade);
    return false;
}

bool TradeRepository::Remove(std::uint64_t tradeId)
{
    std::unique_lock lock(mtx);
    auto trade=m_TradebyId.find(tradeId);
    if(trade == m_TradebyId.end()) return false;
    auto symbol=trade->second.symbol;
    m_TradebyId.erase(trade);

    auto index=m_TradebySymbol.find(symbol);
    if(index!=m_TradebySymbol.end()){
        auto& ids=index->second;
        index->second.erase(std::remove(ids.begin(),ids.end(),tradeId),ids.end());
        if(ids.empty()) m_TradebySymbol.erase(index);

    }
    return true;
}
