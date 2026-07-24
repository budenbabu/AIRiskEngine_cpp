#include "TradeRouteRegistrar.h"

TradeRouteRegistrar::TradeRouteRegistrar(ITradeController &controller):m_controller(controller){}

void TradeRouteRegistrar::RegisterRouter(Router &route)
{
    route.Register(http::verb::post,"/executetrade",ns::AdaptContext(m_controller,&ITradeController::ExecuteTrade));
    route.Register(http::verb::get,"/trades",ns::AdaptContext(m_controller,&ITradeController::GetTrades));
    route.Register(http::verb::get,"/trade/{id}",ns::AdaptContext(m_controller,&ITradeController::GetTradeById));
    route.Register(http::verb::get,"/trade/symbol/{symbol}",ns::AdaptContext(m_controller,&ITradeController::GetTradeBySymbol));
}
