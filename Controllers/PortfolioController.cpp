#include "PortfolioController.h"


PortfolioController::PortfolioController(IPortfolioService &service, HttpResponseFactory &factory,
    IJsonSerializer& serializer,IPositionValidator& validator,ILogger& loggger):m_service(service),m_resposeFactory(factory),
        m_serializer(serializer),m_validator(validator),m_loggger(loggger){}

http::response<http::string_body> PortfolioController::GetPortfolio(const http::request<http::string_body> &request)
{
    auto profolio=m_service.GetPortfolio();
    return m_resposeFactory.OK(profolio,request);
}

http::response<http::string_body> PortfolioController::CreatePortfolio(const http::request<http::string_body> &request)
{
    
    auto position=m_serializer.DeserializeObject<ns::Position>(request.body());
    m_loggger.Info(request.body());
    auto result=m_validator.Validate(position);
    if(!result.IsValid()){
        return m_resposeFactory.BadRequest(result.Errors(),request);
    }    
    return m_resposeFactory.Create(position,request);
}

http::response<http::string_body> PortfolioController::GetSummary(const http::request<http::string_body> &request)
{
    auto summary=m_service.GetSummary();
    return m_resposeFactory.OK(summary,request);
}

http::response<http::string_body> PortfolioController::GetExposureSummary(const http::request<http::string_body> &request)
{
    auto summary=m_service.GetExposureSummary();
    return m_resposeFactory.OK(summary,request);
}

http::response<http::string_body> PortfolioController::GetPnLSummary(const http::request<http::string_body> &request)
{
    auto summary=m_service.GetPnLSummary();
    return m_resposeFactory.OK(summary,request);
}

http::response<http::string_body> PortfolioController::GetconcentrationSummary(const http::request<http::string_body> &request)
{
    auto summary=m_service.GetconcentrationSummary();
    return m_resposeFactory.OK(summary,request);
}
