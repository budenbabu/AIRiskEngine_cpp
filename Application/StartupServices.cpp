#include "StartupServices.h"




StartupServices::StartupServices(PriceLogger &plogger, PortfolioPriceUpdater &updater, 
    WebSocketBroadcaster &broadCaster,TradeAuditLogger& logger,TradeBroadcaster& tbroadCaster,
    PortfolioBroadcaster& pbroadCaster,PortfolioEventPublisher& publisher,DatabaseInitializer& dbInit, 
    RiskRuleLoader& loader, PostgresNotificationListener& listener,IRiskAIQueue& queue):m_queue(queue)
{
    boost::ignore_unused(plogger);
    boost::ignore_unused(broadCaster);
    boost::ignore_unused(updater);
    boost::ignore_unused(logger);
    boost::ignore_unused(tbroadCaster);
    boost::ignore_unused(pbroadCaster);
    boost::ignore_unused(publisher);
    boost::ignore_unused(dbInit);
    boost::ignore_unused(loader);
    boost::ignore_unused(listener);
    m_queue.RecoverPendingJobs();
}