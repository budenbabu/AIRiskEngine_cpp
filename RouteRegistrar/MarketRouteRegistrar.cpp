#include "MarketRouteRegistrar.h"

MarketRouteRegistrar::MarketRouteRegistrar(IMarketDataController &controller):m_controller(controller){}

void MarketRouteRegistrar::RegisterRouter(Router &router)
{
    //router.Register(http::verb::get, "/market",[this](const http::request<http::string_body>& request){ return m_controller.GetQuotes(request); });   
    router.Register(http::verb::get,"/market",ns::Adapt(m_controller,&IMarketDataController::GetQuotes));
}
