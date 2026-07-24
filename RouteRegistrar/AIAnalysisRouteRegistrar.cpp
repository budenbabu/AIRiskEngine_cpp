#include "AIAnalysisRouteRegistrar.h"

AIAnalysisRouteRegistrar::AIAnalysisRouteRegistrar(IAIAnalysisController &controller):m_controller(controller){}

void AIAnalysisRouteRegistrar::RegisterRouter(Router &router)
{
    router.Register(boost::beast::http::verb::get,"/ai/getAll",ns::AdaptContext(m_controller,&IAIAnalysisController::getAll));
    router.Register(boost::beast::http::verb::get,"/ai/getByvid/{vid}",ns::AdaptContext(m_controller,&IAIAnalysisController::getByVid));
    router.Register(boost::beast::http::verb::get,"/ai/getByaid/{aid}",ns::AdaptContext(m_controller,&IAIAnalysisController::getByAid));
}
