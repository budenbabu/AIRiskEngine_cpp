#include "PortfolioRouteRegistrar.h"
#include "../RouteRegistrar/Router.h"


PortfolioRouteRegistrar::PortfolioRouteRegistrar(IPortfolioController& controller):
    m_controller(controller){}

void PortfolioRouteRegistrar::RegisterRouter(Router& router)
{
    // router.Register(http::verb::get,"/portfolio",[this](const auto& request){return m_controller.GetPortfolio(request);});
    // router.Register(http::verb::post,"/portfolio",[this](const auto& request){return m_controller.CreatePortfolio(request);});
    // router.Register(http::verb::get,"/portfolio/summary",[this](const auto& request){return m_controller.GetSummary(request);});
    // router.Register(http::verb::get,"/portfolio/exposure",[this](const auto& request){return m_controller.GetExposureSummary(request);});
    // router.Register(http::verb::get,"/portfolio/pnl",[this](const auto& request){return m_controller.GetPnLSummary(request);});
    // router.Register(http::verb::get,"/portfolio/risk/concentration",[this](const auto& request){return m_controller.GetconcentrationSummary(request);});
    router.Register(http::verb::get,"/portfolio",ns::Adapt(m_controller,&IPortfolioController::GetPortfolio));
    router.Register(http::verb::post,"/portfolio",ns::Adapt(m_controller,&IPortfolioController::CreatePortfolio));
    router.Register(http::verb::get,"/portfolio/summary",ns::Adapt(m_controller,&IPortfolioController::GetSummary));
    router.Register(http::verb::get,"/portfolio/exposure",ns::Adapt(m_controller,&IPortfolioController::GetExposureSummary));
    router.Register(http::verb::get,"/portfolio/pnl",ns::Adapt(m_controller,&IPortfolioController::GetPnLSummary));
    router.Register(http::verb::get,"/portfolio/risk/concentration",ns::Adapt(m_controller,&IPortfolioController::GetconcentrationSummary));
}
