#include "Router.h"

bool Router::MatchRoute(const std::string &route, const std::string &target, RequestContext &context)
{
    auto routeParts=splite(route);
    auto targetPath=splite(target);

    if(routeParts.size() != targetPath.size()) return false;

    for(size_t i=0;i<routeParts.size();++i){
        auto& r=routeParts[i];
        auto& t=targetPath[i];
        if(!r.empty() && r.front()=='{' && r.back()=='}'){
            auto name=r.substr(1,r.size()-2);
            context.setRouterValue(name,t);
            continue;   
        }
        if(r!=t) return false;
    }
    return true;
}

std::vector<std::string> Router::splite(const std::string &str)
{
    std::vector<std::string> result;
    boost::split(result,str,boost::is_any_of("/"),boost::token_compress_on);    
    return result;
}

Router::Router(HealthRouteRegistrar &healthRouteRegistrar,
               PortfolioRouteRegistrar &portfolioRouteRegistrar, HttpResponseFactory &factory,
               MarketRouteRegistrar &marketRegistrar, TradeRouteRegistrar &tradeRegistrar,
               RiskRuleRouteRegistrar& riskregistrar,AIAnalysisRouteRegistrar& aIAnalysisRouteRegistrar,
               ILogger &logger) : m_factory(factory), m_logger(logger)
{
    healthRouteRegistrar.RegisterRouter(*this);
    portfolioRouteRegistrar.RegisterRouter(*this);
    marketRegistrar.RegisterRouter(*this);
    tradeRegistrar.RegisterRouter(*this);
    riskregistrar.RegisterRouter(*this);
    aIAnalysisRouteRegistrar.RegisterRouter(*this);
}

void Router::Handler(RequestContext &context)
{
    auto& request=context.GetRequest();
    
    auto target=std::string(request.target());
    for(auto& [key,handle] : m_routes){
        if(key.method != request.method()) continue;
        if(MatchRoute(key.path,target,context)){
            handle(context);
            return;
        }
    }
    
    m_logger.Error(std::format("Router::Handler not found {} {}",static_cast<int>(request.method()),target));

    context.setResponse(m_factory.NotFound(R"({"message":"Route not found"})",request));


        //Old impl
        //td::cout<<"Router::Handler Method: "<<request.method()<<" "<<request.target()<<std::endl;
        //RouteKey key{.method=request.method(),.path=std::string(request.target())};
        //auto it=m_routes.find(key);
        // if(it==m_routes.end()) {
        //     m_logger.Error(std::format("Router::Handler not found {} {}", static_cast<int>(request.method()),request.target()));            
        //     context.setResponse(m_factory.NotFound("Rout Not Found",request));
        //     return;
        // }
        // it->second(context); //new added        
    
        //m_logger.Error(std::format("Router::Handler {} {} ex: {}", static_cast<int>(request.method()),request.target(),ex.what())); 
}

void Router::Register(http::verb method, std::string path, HandlerFuc handler)
{
    m_routes.emplace(RouteKey{method,std::move(path)},std::move(handler));
}

http::response<http::string_body> HealthController::getStatus(const http::request<http::string_body>& request)
{
    http::response<http::string_body> response(http::status::ok, request.version());
    response.keep_alive(request.keep_alive());
    response.set(http::field::server,"AI-Risk-Assistant");
    response.set(http::field::content_type, "application/json");
    response.body() = R"({"status":"OK"})";
    response.prepare_payload();
    return response;
}
