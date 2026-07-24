#include "InMemoryPortfolioRepository.h"
#include <boost\core\ignore_unused.hpp>

InMemoryPortfolioRepository::InMemoryPortfolioRepository(ILogger& logger):m_logger(logger)
{
    m_positions.emplace("AAPL",ns::Position{ "AAPL",100,185.25,194.80 });
    m_positions.emplace("MSFT",ns::Position{ "MSFT",50,510.80,525.30 });
    m_positions.emplace("NVDA",ns::Position{ "NVDA",25,170.30,181.60 });
    m_positions.emplace("GOOGL",ns::Position{ "GOOGL",40,172.10,169.40 });
    //std::cout<< "PortfolioRepository: "<< this<< std::endl;
}

std::vector<ns::Position> InMemoryPortfolioRepository::GePositions() const
{
    std::shared_lock lock(mtx);
    std::vector<ns::Position> result;
    result.reserve(m_positions.size());
    for (const auto& [symbol, position] : m_positions) result.push_back(position);
    return result;
}

std::optional<ns::Position> InMemoryPortfolioRepository::GetBySymbol(const std::string& symbol) const
{
    std::shared_lock lock(mtx);
    if(auto it=m_positions.find(symbol); it!=m_positions.end()) return std::optional<ns::Position>{it->second};
    return std::nullopt;
    // auto it = m_positions.find(symbol);
    // if (it == m_positions.end()) return std::nullopt;
    // return it->second;
}

bool InMemoryPortfolioRepository::Add(const ns::Position& position)
{
    std::unique_lock lock(mtx);
    return m_positions.emplace(position.symbol, position).second;
}

bool InMemoryPortfolioRepository::Update(const ns::Position& position)
{
    std::unique_lock lock(mtx);
    auto it = m_positions.find(position.symbol);
    if (it == m_positions.end()) return false;   
   // m_logger.Info(std::format("before {} {}",it->second.symbol,it->second.quantity));
    it->second = position;   
  //  m_logger.Info(std::format("after {} {}",it->second.symbol,it->second.quantity));
    return true;
}

bool InMemoryPortfolioRepository::Remove(const std::string& symbol)
{
    std::unique_lock lock(mtx);
    return m_positions.erase(symbol) > 0;
}

bool InMemoryPortfolioRepository::UpdateMarketPrice(const std::string& symbol, double marketPrice)
{
    auto it = m_positions.find(symbol);
    if (it == m_positions.end()) return false;
    it->second.marketPrice = marketPrice;
    return true;
}

bool InMemoryPortfolioRepository::Upsert(pqxx::transaction_base &tx, const ns::Position &position)
{
    boost::ignore_unused(tx);
    boost::ignore_unused(position);
    return false;
}

std::optional<ns::Position> InMemoryPortfolioRepository::GetBySymbol(pqxx::transaction_base &tx, const std::string &symbol) const
{
    boost::ignore_unused(tx);
    boost::ignore_unused(symbol);
    return std::optional<ns::Position>();
}

bool InMemoryPortfolioRepository::Remove(pqxx::transaction_base &tx, const std::string &symbol)
{
    boost::ignore_unused(tx);
    boost::ignore_unused(symbol);
    return false;
}
