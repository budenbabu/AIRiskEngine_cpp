#include "HttpResponseFactory.h"

http::response<http::string_body> HttpResponseFactory::BuildResponse(http::status status, const std::string &body, const http::request<http::string_body> &request) const
{
    http::response<http::string_body> response{status,request.version()};
    response.keep_alive(request.keep_alive());
    response.set(http::field::server,"AI-Risk-Assistant");
    response.set(http::field::content_type,"application/json");
    response.body()=body;
    response.prepare_payload();
    return response;
}

HttpResponseFactory::HttpResponseFactory(IJsonSerializer &serializer) : m_serializer(serializer) {}




http::response<http::string_body> HttpResponseFactory::BadRequest(const std::vector<std::string>& body,const http::request<http::string_body>& request) const
{

    nlohmann::json json=body;

    return BuildResponse(http::status::bad_request,m_serializer.Serialize(json),request);
}

http::response<http::string_body> HttpResponseFactory::NotFound(const std::string &body,const http::request<http::string_body>& request) const
{
    nlohmann::json json{
        {"error", body}
    };
    return BuildResponse(http::status::not_found,m_serializer.Serialize(json),request);
}

http::response<http::string_body> HttpResponseFactory::InterServerError(const std::string &body,const http::request<http::string_body>& request) const
{
    nlohmann::json json{
        {"error", body}
    };
    return BuildResponse(http::status::internal_server_error,m_serializer.Serialize(json),request);
}
