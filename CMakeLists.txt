cmake_minimum_required(VERSION 3.10.0)
project(TestBoostDI VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

    foreach(lang C CXX)
        string(REPLACE "/MDd" "/MT" CMAKE_${lang}_FLAGS_DEBUG "${CMAKE_${lang}_FLAGS_DEBUG}")
        string(REPLACE "/MD" "/MT" CMAKE_${lang}_FLAGS_RELEASE "${CMAKE_${lang}_FLAGS_RELEASE}")
        string(REPLACE "/MD" "/MT" CMAKE_${lang}_FLAGS_RELWITHDEBINFO "${CMAKE_${lang}_FLAGS_RELWITHDEBINFO}")
        string(REPLACE "/MD" "/MT" CMAKE_${lang}_FLAGS_MINSIZEREL "${CMAKE_${lang}_FLAGS_MINSIZEREL}")
    endforeach()
endif()

set(BOOST_ROOT "E:\\boost_1_91_0")
set(BOOST_DI_ROOT "E:\\local\\di-cpp14\\di-cpp14")
set(nlohmann "E:\\json-develop\\include")
set(PQXX "E:\\vcpkg\\installed\\x64-windows-static")
set(LIBPQ "E:\\vcpkg\\installed\\x64-windows-static")

include_directories(${BOOST_ROOT})
include_directories(${BOOST_DI_ROOT}\\include)
include_directories(${BOOST_DI_ROOT}\\extension\\include)
include_directories(${nlohmann})
include_directories(${PQXX}\\include)
include_directories(${LIBPQ}\\include)
link_directories(${BOOST_ROOT}/lib64-msvc-14.3)
link_directories(${PQXX}\\lib)
link_directories(${LIBPQ}\\lib)


if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0601)
endif()

add_executable(TestBoostDI main.cpp
    HttpServer.h
    Listener.h
    Listener.cpp
    RouteRegistrar/Router.h
    RouteRegistrar/Router.cpp
    Sessions/Session.h
    Sessions/Session.cpp
    Sessions/ISessionFactory.h
    Sessions/SessionFactory.h
    Sessions/SessionFactory.cpp
    RouteRegistrar/RouteKey.h
    RouteRegistrar/IRouteRegistrar.h
    RouteRegistrar/HealthRouteRegistrar.h
    RouteRegistrar/HealthRouteRegistrar.cpp
    Common/JsonSerializer.h
    Common/IJsonSerializer.h
    Common/NlohmannJsonSerializer.h
    Common/NlohmannJsonSerializer.cpp
    Models/Position.h
    Common/http/IHttpResponseFactory.h
    Common/http/HttpResponseFactory.h
    Common/http/HttpResponseFactory.cpp
    Repository/IPortfolioRepository.h    
    Service/IPortfolioService.h
    Service/PortfolioService.h
    Service/PortfolioService.cpp
    Controllers/IPortfolioController.h
    Controllers/PortfolioController.h
    Controllers/PortfolioController.cpp
    RouteRegistrar/PortfolioRouteRegistrar.h
    RouteRegistrar/PortfolioRouteRegistrar.cpp    
    Middleware/Middleware.h
    Middleware/IRequestHandler.h
    Middleware/ExceptionMiddleware.h
    Middleware/ExceptionMiddleware.cpp
    pipeline/RequestPipeline.h
    Loogger/ILogger.h
    Loogger/ConsoleLogger.h
    Middleware/LoggingMiddleware.h
    Middleware/LoggingMiddleware.cpp
    Models/Portfolio.h
    Database/Database.h
    pipeline/RequestContext.h
    Validation/ValidationResult.h
    Validation/IPostionValidator.h
    Validation/PositionValidator.h
    Validation/PositionValidator.cpp
    Modules/HttpModule.h
    Domain/Portfolio/PortfolioSummary.h
    Domain/Portfolio/IPortfolioCalculator.h
    Domain/Portfolio/PortfolioCalculator.h
    Domain/Portfolio/PortfolioCalculator.cpp
    Domain/Market/Quote.h
    Domain/Market/IMarketDataService.h
    Domain/Market/MarketDataService.h
    Domain/Market/MarketDataService.cpp 
    Domain/Analytics/Exposures/Exposure.h 
    Domain/Risk/RiskSummary.h 
    Domain/Risk/IRiskCalculator.h
    Domain/Analytics/Exposures/ExposureSummary.h
    Domain/Analytics/Exposures/IExposureCalculator.h
    Domain/Analytics/Exposures/ExposureCalculator.h
    Domain/Analytics/Exposures/ExposureCalculator.cpp
    Domain/Analytics/IPortfolioAnalyticsService.h
    Domain/Analytics/PortfolioAnalyticsService.cpp
    Domain/Analytics/PortfolioAnalyticsService.h
    Domain/Analytics/PnL/PnL.h
    Domain/Analytics/PnL/IPnLCalculator.h
    Domain/Analytics/PnL/PnLCalculator.cpp
    Domain/Analytics/PnL/PnLCalculator.cpp
    Domain/Analytics/Common/PositionMetrics.h
    Domain/Analytics/Common/PositionMetricsCalculator.h
    Domain/Analytics/Common/PositionMetricsCalculator.cpp
    Domain/Analytics/Common/IPositionMetricsCalculator.h
    Domain/Market/IMarketPriceGenerator.h
    Domain/Market/MarketPriceGenerator.h
    Domain/Market/MarketPriceGenerator.cpp
    Controllers/IMarketDataController.h
    Controllers/MarketDataController.h
    Controllers/MarketDataController.cpp
    RouteRegistrar/MarketRouteRegistrar.h
    RouteRegistrar/MarketRouteRegistrar.cpp
    Domain/Risk/Concentration/ConcentrationRisk.h
    Domain/Risk/Concentration/IConcentrationCalculator.h
    Domain/Risk/Concentration/ConcentrationCalculator.h
    Domain/Risk/Concentration/ConcentrationCalculator.cpp
    Infrastructure/PriceEvent/PriceUpdatedEvent.h
    Infrastructure/PriceEvent/IMarketEvents.h
    Infrastructure/PriceEvent/MarketEvents.h
    Infrastructure/PriceEvent/MarketEvents.cpp
    Common/PriceLogger.h
    Common/PriceLogger.cpp 
    Application/Subscribers/PortfolioPriceUpdater.h 
    Application/Subscribers/PortfolioPriceUpdater.cpp    
    Application/WebSocket/IWebSocketSession.h
    Application/WebSocket/IWebSocketHub.h 
    Application/WebSocket/WebSocketHub.h
    Application/WebSocket/WebSocketHub.cpp 
    Application/WebSocket/WebSocketBroadcaster.h
    Application/WebSocket/WebSocketBroadcaster.cpp 
    Application/WebSocket/WebSocketSession.h
    Application/WebSocket/WebSocketSession.cpp
    Application/WebSocket/IWebSocketSessionFactory.h
    Application/WebSocket/WebSocketSessionFactory.h
    Application/WebSocket/WebSocketSessionFactory.cpp
    Application/WebSocket/WebSocketListener.h
    Application/WebSocket/WebSocketListener.cpp
    Application/Application.h
    Application/Application.cpp
    Application/StartupServices.h
    Application/StartupServices.cpp
    Domain/Trade/Trade.h
    Domain/Trade/TradeSide.h
    Service/Trade/ITradeService.h
    Service/Trade/TradeService.h
    Service/Trade/TradeService.cpp
    Repository/Trade/ITradeRepository.h    
    Infrastructure/TradeEvent/TradeExecutedEvent.h
    Test/TradeAuditLogger.h
    Test/TradeAuditLogger.cpp
    Controllers/ITradeController.h
    Controllers/TradeController.h
    Validation/ITraadeValidator.h
    Controllers/TradeController.cpp
    RouteRegistrar/TradeRouteRegistrar.h
    RouteRegistrar/TradeRouteRegistrar.cpp
    RouteRegistrar/RouteAdapter.h
    Infrastructure/TradeEvent/TradeBroadcaster.h
    Infrastructure/TradeEvent/TradeBroadcaster.cpp
    Infrastructure/PortfolioEvent/PortfolioUpdatedEvent.h
    Infrastructure/PortfolioEvent/PortfolioBroadcaster.h
    Infrastructure/PortfolioEvent/PortfolioBroadcaster.cpp
    Infrastructure/PortfolioEvent/PortfolioEventPublisher.h
    Infrastructure/PortfolioEvent/PortfolioEventPublisher.cpp
    Database/DatabaseConfig.h    
    Database/DatabaseInitializer.h
    Database/DatabaseInitializer.cpp
    Repository/Trade/PostgresTradeRepository.h
    Repository/Trade/PostgresTradeRepository.cpp
    Repository/PostgresPortfolioRepository.h
    Repository/PostgresPortfolioRepository.cpp
    Database/PostgreSqlConnectionPool.h
    Database/PostgreSqlConnectionPool.cpp
    Database/PoolConnection.h
    Database/PoolConnection.cpp
    RiskRule/RiskResult.h
    RiskRule/IRiskRule.h
    RiskRule/MaxTradeQuantityRule.h
    RiskRule/MaxTradeQuantityRule.cpp
    RiskRule/RiskEngine.h
    RiskRule/RiskEngine.cpp
    Repository/Risk/IRiskRuleRepository.h
    Repository/Risk/PostgresRiskRuleRepository.h
    Repository/Risk/PostgresRiskRuleRepository.cpp 
    RiskRule/RiskRuleFactory.h
    RiskRule/RiskRuleFactory.cpp 
    RiskRule/RiskRuleLoader.h 
    RiskRule/RiskRuleLoader.cpp 
    Database/RiskRuleNotificationReceiver.h 
    Database/RiskRuleNotificationReceiver.cpp 
    Database/PostgresNotificationListener.h
    Database/PostgresNotificationListener.cpp 
    Controllers/IRiskRuleController.h 
    Controllers/RiskRuleController.h 
    Controllers/RiskRuleController.cpp
    RouteRegistrar/RiskRuleRouteRegistrar.h
    RouteRegistrar/RiskRuleRouteRegistrar.cpp
    Repository/Risk/Violation/IRiskViolationRepository.h
    Repository/Risk/Violation/RiskViolationRepository.h
    Repository/Risk/Violation/RiskViolationRepository.cpp 
    RiskAnalysisService/RiskAIAnalysis.h         
    RiskAnalysisService/Repository/IRiskAIAnalysisRepository.h
    RiskAnalysisService/Repository/RiskAIAnalysisRepository.h 
    RiskAnalysisService/Repository/RiskAIAnalysisRepository.cpp
    RiskAnalysisService/ai/PromptBuilder.h 
    RiskAnalysisService/ai/PromptBuilder.cpp
    RiskAnalysisService/ai/IAIService.h
    RiskAnalysisService/ai/OllamaService.h
    RiskAnalysisService/ai/OllamaService.cpp
    
    RiskAnalysisService/Services/RiskAnalysisService.cpp 
    RiskAnalysisService/Services/RiskAnalysisService.h
    RiskAnalysisService/Services/IRiskAIAnalysisService.h
    RiskAnalysisService/Services/IRiskAIQueue.h 
    RiskAnalysisService/Services/RiskAIQueue.h 
    RiskAnalysisService/Services/RiskAIQueue.cpp 
    RiskAnalysisService/ai/AIExecutor.h 
    RiskAnalysisService/ai/AIExecutor.cpp
    App/ApplicationStartup.h
    App/IApplicationStartup.h
    App/ApplicationStartup.cpp
    RiskAnalysisService/Repository/IAIJobRepository.h
    RiskAnalysisService/Repository/AIJobRepository.h
    RiskAnalysisService/Repository/AIJobRepository.cpp
    Service/AI/IAIAnalysisService.h
    Service/AI/AIAnalysisService.h
    Service/AI/AIAnalysisService.cpp
    Controllers/IAIAnalysisController.h
    Controllers/AIAnalysisController.cpp
    Controllers/AIAnalysisController.h
    RouteRegistrar/AIAnalysisRouteRegistrar.h
    RouteRegistrar/AIAnalysisRouteRegistrar.cpp)

    

if(MSVC)
    target_compile_options(TestBoostDI PRIVATE /bigobj /FS /W4 /WX)
    target_link_libraries(TestBoostDI PRIVATE pqxx libpq libpgcommon libpgport libecpg libecpg_compat libpgtypes libcrypto libssl secur32 wldap32 ws2_32 crypt32)
endif()

set(DLL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

message(STATUS "Looking for DLLs in: ${DLL_SOURCE_DIR}")
set(MY_REQUIRED_DLLS
    "${DLL_SOURCE_DIR}/libcrypto-3-x64.dll"
    "${DLL_SOURCE_DIR}/zlib1.dll"
    "${DLL_SOURCE_DIR}/libssl-3-x64.dll" 
)

add_custom_command(TARGET TestBoostDI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${MY_REQUIRED_DLLS}
    $<TARGET_FILE_DIR:TestBoostDI>
)