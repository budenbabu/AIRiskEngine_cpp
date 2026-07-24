#pragma once

#include <boost\beast\http.hpp>
#include <boost\algorithm\string.hpp>
#include <format>
#include <functional>
#include <unordered_map>
#include "RouteKey.h"
#include "RouteAdapter.h"
#include "../Middleware/IRequestHandler.h"
#include "../RouteRegistrar/HealthRouteRegistrar.h"
#include "../RouteRegistrar/PortfolioRouteRegistrar.h"
#include "../Common/http/HttpResponseFactory.h"
#include "MarketRouteRegistrar.h"
#include "TradeRouteRegistrar.h"
#include "AIAnalysisRouteRegistrar.h"
#include "RiskRuleRouteRegistrar.h"
#include "../Loogger/ILogger.h"


namespace http=boost::beast::http;

class HealthRouteRegistrar;
class PortfolioRouteRegistrar;
class HttpResponseFactory;
class MarketRouteRegistrar;
class TradeRouteRegistrar;
class RiskRuleRouteRegistrar;
class AIAnalysisRouteRegistrar;
//using HandlerFuc=std::function<http::response<http::string_body>(const http::request<http::string_body>&)>;

using HandlerFuc=std::function<void(RequestContext&)>;

class IRouter:public IRequestHandler
{
public:    
    virtual ~IRouter()=default;
//     virtual http::response<http::string_body> Handele(const http::request<http::string_body>& request)=0;
};

class IHealthController
{
public:
    virtual ~IHealthController() = default;
    virtual http::response<http::string_body> getStatus(const http::request<http::string_body>&) = 0;
};

class HealthController : public IHealthController {
public:
    http::response<http::string_body> getStatus(const http::request<http::string_body>&) override;
};




class Router : public IRouter {    
    std::unordered_map<RouteKey,HandlerFuc,RoutKeyHash> m_routes;
    HttpResponseFactory& m_factory;
    ILogger& m_logger;

    bool MatchRoute(const std::string& route,const std::string& target,RequestContext& context);
    std::vector<std::string> splite(const std::string& str);
public:
    explicit Router(HealthRouteRegistrar& healthRouteRegistrar,
            PortfolioRouteRegistrar& portfolioRouteRegistrar,HttpResponseFactory& factory,
            MarketRouteRegistrar& marketRegistrar,TradeRouteRegistrar& tradeRegistrar,
            RiskRuleRouteRegistrar& riskregistrar,AIAnalysisRouteRegistrar& aIAnalysisRouteRegistrar,
            ILogger& logger);
    void Handler(RequestContext& context)override;
    void Register(http::verb method,std::string path,HandlerFuc handler);
    
};