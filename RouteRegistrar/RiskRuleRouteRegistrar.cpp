#include "RiskRuleRouteRegistrar.h"

RiskRuleRouteRegistrar::RiskRuleRouteRegistrar(IRiskRuleController &controller):m_controller(controller){}

void RiskRuleRouteRegistrar::RegisterRouter(Router &router)
{
    router.Register(http::verb::get,"/risk/rule", ns::AdaptContext(m_controller,&IRiskRuleController::getRules));
    router.Register(http::verb::post,"/risk/addrule", ns::AdaptContext(m_controller,&IRiskRuleController::addRule));
    router.Register(http::verb::post,"/risk/update/{id}", ns::AdaptContext(m_controller,&IRiskRuleController::updatedRule));
    router.Register(http::verb::post,"/risk/delete/{id}", ns::AdaptContext(m_controller,&IRiskRuleController::deleteRule));
    router.Register(http::verb::get, "/risk/violations", ns::AdaptContext(m_controller, &IRiskRuleController::riskViolation));
    router.Register(http::verb::get, "/risk/violationsbySymbol/{symbol}", ns::AdaptContext(m_controller, &IRiskRuleController::riskViolationBySymbol));
    router.Register(http::verb::get, "/risk/violationsbyType/{type}", ns::AdaptContext(m_controller, &IRiskRuleController::riskViolationByType));
    router.Register(http::verb::get, "/risk/analysis/{id}", ns::AdaptContext(m_controller, &IRiskRuleController::GenerateAnalysis));
}
