#include "HttpResponseBuilder.h"

http::response<http::string_body> HttpResponseBuilder::ok(const std::string &body, unsigned version, bool keepAlive)
{
    http::response<http::string_body> response{
        http::status::ok,
        version
    };

    response.keep_alive(keepAlive);

    response.set(
        http::field::content_type,
        "application/json");

    response.body() = body;

    response.prepare_payload();

    return response;
}

http::response<http::string_body> HttpResponseBuilder::NotFound(unsigned version, bool keepAlive)
{
    return http::response<http::string_body>();
}

http::response<http::string_body> HttpResponseBuilder::BadRequest(const std::string &body, unsigned version, bool keepalive)
{
    return http::response<http::string_body>();
}
