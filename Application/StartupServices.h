#pragma once
#include <boost/core/ignore_unused.hpp>
#include "../Application/Subscribers/PortfolioPriceUpdater.h"
#include "../Application/WebSocket/WebSocketBroadcaster.h"
#include "../Test/TradeAuditLogger.h"
#include "../Infrastructure/TradeEvent/TradeBroadcaster.h"
#include "../Infrastructure/PortfolioEvent/PortfolioBroadcaster.h"
#include "../Infrastructure/PortfolioEvent/PortfolioEventPublisher.h"
#include "../Database/DatabaseInitializer.h"
#include "../RiskRule/RiskRuleLoader.h"
#include "../Database/PostgresNotificationListener.h"
#include "../RiskAnalysisService/Services/RiskAIQueue.h"


class PriceLogger;
class PortfolioPriceUpdater;
class WebSocketBroadcaster;
class TradeAuditLogger;
class TradeBroadcaster;
class RiskAIQueue;

class StartupServices{
    IRiskAIQueue& m_queue;
public:
    StartupServices(PriceLogger& plogger,PortfolioPriceUpdater& updater,
        WebSocketBroadcaster& broadCaster,TradeAuditLogger& logger,TradeBroadcaster& tbroadCaster,
        PortfolioBroadcaster& pbroadCaster,PortfolioEventPublisher& publisher,DatabaseInitializer& dbInit, 
        RiskRuleLoader& loader, PostgresNotificationListener& listener,IRiskAIQueue& queue);
};
