#pragma once

#include <iostream>
#include <format>
#include "../../Repository/Trade/ITradeRepository.h"
#include "../../Repository/IPortfolioRepository.h"
#include "../../Infrastructure/PriceEvent/IMarketEvents.h"
#include "../../Database/PostgreSqlConnectionPool.h"
#include "../../RiskRule/RiskEngine.h"
#include "ITradeService.h"
#include "../../Loogger/ILogger.h"
#include "../../Repository/Risk/Violation/IRiskViolationRepository.h"
#include "../../Common/IJsonSerializer.h"
#include "../../Application/WebSocket/IWebSocketHub.h"
#include "../../RiskAnalysisService/Services/RiskAIQueue.h"


class TradeService: public ITradeService{
    ITradeRepository& m_trepositor;
    IPortfolioRepository& m_prepositiry;
    PostgreSqlConnectionPool& m_db;
    IRiskViolationRepository& m_violation;
    IMarketEvents& m_marketEvent;        
    IJsonSerializer& m_serializer;
    IWebSocketHub& m_hub;
    RiskEngine& m_engine;    
    IRiskAIQueue& m_aiQueue;        
    ILogger& m_logger;
    bool Sell(const ns::Trade& trade,const std::optional<ns::Position>& postion,pqxx::transaction_base& tx);
    bool Buy(const ns::Trade& trade,const std::optional<ns::Position>& postion,pqxx::transaction_base& tx);
public:
    TradeService(ITradeRepository& trepositor,IPortfolioRepository& prepositiry,IMarketEvents& marketEvent,ILogger& logger, PostgreSqlConnectionPool& db,
        RiskEngine& engine,IRiskViolationRepository& violation, IJsonSerializer& serializer, IWebSocketHub& hub,IRiskAIQueue& aiQueue);
    bool Execute(const ns::Trade& trade)override;
    std::vector<ns::Trade> GetTrades() const override;
    virtual std::optional<ns::Trade> GetTrade(std::uint64_t tradeId) const override;
    virtual std::vector<ns::Trade> GetSymbolBytrade(const std::string& symbol)const override;
};