//#define _WIN32_WINNT 0x0601
#pragma once

#include <iostream>
#include <boost\asio.hpp>
#include <boost\di.hpp>

#include "../Common/http/HttpResponseFactory.h"
#include "../Common/NlohmannJsonSerializer.h"
#include "../RouteRegistrar/HealthRouteRegistrar.h"
#include "../RouteRegistrar/PortfolioRouteRegistrar.h"
#include "../RouteRegistrar/Router.h"
#include "../Service/IPortfolioService.h"
#include "../Service/PortfolioService.h"
#include "../Controllers/PortfolioController.h"
#include "../Sessions/ISessionFactory.h"
#include "../Sessions/SessionFactory.h"
#include "../Listener.h"
#include "../HttpServer.h"
#include "../Loogger/ConsoleLogger.h"
#include "../Domain/Portfolio/PortfolioCalculator.h"
#include "../Domain/Market/IMarketDataService.h"
#include "../Domain/Market/MarketDataService.h"
#include "../Domain/Analytics/Exposures/ExposureCalculator.h"
#include "../Domain/Analytics/PortfolioAnalyticsService.h"
#include "../Domain/Analytics/PnL/PnLCalculator.h"
#include "../Domain/Analytics/Common/PositionMetricsCalculator.h"
#include "../Domain/Market/MarketPriceGenerator.h"
#include "../Controllers/MarketDataController.h"
#include "../Domain/Risk/Concentration/ConcentrationCalculator.h"
#include "../Infrastructure/PriceEvent/MarketEvents.h"
#include "../Common/PriceLogger.h"
#include "../Application/Subscribers/PortfolioPriceUpdater.h"
#include "../Application/WebSocket/WebSocketHub.h"
#include "../Application/WebSocket/WebSocketBroadcaster.h"
#include "../Application/WebSocket/WebSocketSession.h"
#include "../Application/WebSocket/WebSocketSessionFactory.h"
#include "../Application/WebSocket/WebSocketListener.h"
#include "../Application/Application.h"
#include "../Application/StartupServices.h"
#include "../Service/Trade/TradeService.h"
#include "../Test/TradeAuditLogger.h"
#include "../Controllers/TradeController.h"
#include "../RouteRegistrar/TradeRouteRegistrar.h"
#include "../Infrastructure/TradeEvent/TradeBroadcaster.h"
#include "../Infrastructure/PortfolioEvent/PortfolioEventPublisher.h"
#include "../Database/DatabaseConfig.h"
#include "../Database/PostgreSqlConnection.h"
#include "../Database/DatabaseInitializer.h"
#include "../Repository/Trade/PostgresTradeRepository.h"
#include "../Repository/PostgresPortfolioRepository.h"
#include "../Database/PostgreSqlConnectionPool.h"
#include "../RiskRule/RiskEngine.h"
#include "../RiskRule/RiskRuleFactory.h"
#include "../RiskRule/RiskRuleLoader.h"
#include "../Repository/Risk/PostgresRiskRuleRepository.h"
#include "../Database/PostgresNotificationListener.h"
#include "../Controllers/RiskRuleController.h"
#include "../Repository/Risk/Violation/RiskViolationRepository.h"
#include "../RiskAnalysisService/Repository/RiskAIAnalysisRepository.h"
#include "../RiskAnalysisService/Services/RiskAnalysisService.h"
#include "../RiskAnalysisService/Services/RiskAIQueue.h"
#include "../RiskAnalysisService/ai/OllamaService.h"
#include "../RiskAnalysisService/ai/AIExecutor.h"
#include "../RiskAnalysisService/Repository/AIJobRepository.h"
#include "../Service/AI/AIAnalysisService.h"
#include "../Controllers/AIAnalysisController.h"
#include "../App/ApplicationStartup.h"




namespace di=boost::di;

auto HttpModule(){
    return di::make_injector(

        di::bind<HttpResponseFactory>.in(di::singleton),
        di::bind<IJsonSerializer>().to<NlohmannJsonSerializer>().in(di::singleton),        
        di::bind<IHealthController>().to<HealthController>().in(di::singleton),        
        di::bind<HealthRouteRegistrar>.in(di::singleton),
        di::bind<IPortfolioRepository>().to<PostgresPortfolioRepository>().in(di::singleton),
        di::bind<IPortfolioService>().to<PortfolioService>().in(di::singleton),
        di::bind<IPortfolioController>().to<PortfolioController>().in(di::singleton),
        di::bind<PortfolioRouteRegistrar>().in(di::singleton),
        di::bind<ITradeController>().to<TradeController>().in(di::singleton),
        di::bind<TradeRouteRegistrar>().in(di::singleton),
        di::bind<IRiskRuleController>().to<RiskRuleController>().in(di::singleton),
        di::bind<RiskRuleRouteRegistrar>().in(di::singleton),
        di::bind<IAIAnalysisController>().to<AIAnalysisController>().in(di::singleton),
        di::bind<AIAnalysisRouteRegistrar>().in(di::singleton),
        di::bind<IRouter>().to<Router>().in(di::singleton)
        //di::bind<IRequestHandler>().to<Router>().in(di::sclsingleton),                
        // di::bind<ISessionFactory>().to<SessionFactory>().in(di::singleton),    
        // di::bind<Listener>().in(di::singleton),    
        // di::bind<IHttpServer>().to<HttpServer>().in(di::singleton)
    );
}
auto MarketModule()
{
    return di::make_injector(
        di::bind<IMarketDataService>().to<MarketDataService>().in(di::singleton),
        di::bind<IMarketPriceGenerator>().to<MarketPriceGenerator>().in(di::singleton),
        di::bind<IMarketDataController>().to<MarketDataController>().in(di::singleton),
        di::bind<MarketRouteRegistrar>().in(di::singleton),
        di::bind<IMarketEvents>().to<MarketEvents>().in(di::singleton),
        di::bind<PriceLogger>().in(di::singleton),
        di::bind<PortfolioPriceUpdater>().in(di::singleton),
        di::bind<TradeAuditLogger>().in(di::singleton),
        di::bind<TradeBroadcaster>().in(di::singleton),
        di::bind<PortfolioBroadcaster>().in(di::singleton),
        di::bind<PortfolioEventPublisher>().in(di::singleton)
    );
}

auto CommonModdule(){
    return di::make_injector(
        di::bind<ILogger>().to<ConsoleLogger>().in(di::singleton),      
        di::bind<IPositionMetricsCalculator>().to<PositionMetricsCalculator>().in(di::singleton),      
        di::bind<IPortfolioCalculator>().to<PortfolioCalculator>().in(di::singleton),        
        di::bind<IExposureCalculator>().to<ExposureCalculator>().in(di::singleton),
        di::bind<IPnLCalculator>().to<PnLCalculator>().in(di::singleton),
        di::bind<IConcentrationCalculator>().to<ConcentrationCalculator>().in(di::singleton),
        di::bind<IPortfolioAnalyticsService>().to<PortfolioAnalyticsService>().in(di::singleton)
        
    );
}

auto ValidatorModdule(){
    return di::make_injector(
        di::bind<IPositionValidator>().to<PositionValidator>().in(di::singleton),
        di::bind<RiskRuleFactory>().in(di::singleton),
        di::bind<RiskEngine>().in(di::singleton),
        di::bind<IRiskRuleRepository>().to<PostgresRiskRuleRepository>().in(di::singleton),
        di::bind<RiskRuleLoader>().in(di::singleton),
        di::bind<IRiskViolationRepository>().to<RiskViolationRepository>().in(di::singleton),
        di::bind<IRiskAIAnalysisRepository>().to<RiskAIAnalysisRepository>().in(di::singleton),
        di::bind<IAIService>().to<OllamaService>().in(di::singleton),     
        di::bind<IRiskAIAnalysisService>().to<RiskAIAnalysisService>().in(di::singleton),
        di::bind<std::size_t>().to(static_cast<std::size_t>(2)),
        di::bind<AIExecutor>().in(di::singleton),        
        //di::bind<AIExecutor>().to([] {return std::make_shared<AIExecutor>(static_cast<std::size_t>(2));}).in(di::singleton),
        //di::bind<AIExecutor>().to(AIExecutor(2)).in(di::singleton),
        di::bind<IAIJobRepository>().to<AIJobRepository>().in(di::singleton),
        di::bind<IRiskAIQueue>().to<RiskAIQueue>().in(di::singleton),
        di::bind<IAIAnalysisService>().to<AIAnalysisService>().in(di::singleton)
    );
}

auto WebsocketModule() {
    return di::make_injector(
        di::bind<IWebSocketHub>().to<WebSocketHub>().in(di::singleton),
        di::bind<WebSocketBroadcaster>().in(di::singleton),
        di::bind<IWebSocketSession>().to<WebSocketSession>().in(di::singleton),
        di::bind<IWebSocketSessionFactory>().to<WebSocketSessionFactory>().in(di::singleton),
        di::bind<WebSocketListener>().in(di::singleton)
    );
}

auto AppModule(){
    return di::make_injector(
        di::bind<StartupServices>().in(di::singleton),
        di::bind<Application>().in(di::singleton)
        //di::bind<IApplicationStartup>().to<ApplicationStartup>()        
    );
}

auto TradeModule(){
    return di::make_injector(
        di::bind<ITradeRepository>().to<PostgresTradeRepository>().in(di::singleton),
        di::bind<ITradeService>().to<TradeService>().in(di::singleton)
    );
}

auto DbModule(){
    return di::make_injector(
        di::bind<DataBaseConfig>().in(di::singleton),   
        di::bind<DatabaseInitializer>().in(di::singleton),
        di::bind<PostgreSqlConnectionPool>().in(di::singleton),
        di::bind<PostgresNotificationListener>().in(di::singleton)
    );
}


