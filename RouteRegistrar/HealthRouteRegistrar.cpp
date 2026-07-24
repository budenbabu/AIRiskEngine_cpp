#include "HealthRouteRegistrar.h"


HealthRouteRegistrar::HealthRouteRegistrar(IHealthController &controller):m_controller(controller)
{
}

void HealthRouteRegistrar::RegisterRouter(Router &router)
{
    // router.Register(http::verb::get, "/health",
    //     [this](const http::request<http::string_body>& request){ return m_controller.getStatus(request); });

    router.Register(http::verb::get,"/health",ns::Adapt(m_controller,&IHealthController::getStatus));
}
