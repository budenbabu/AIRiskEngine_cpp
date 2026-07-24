#pragma once
#include <boost\beast.hpp>
#include <boost\asio.hpp>

#include <iostream>
#include <memory>
#include <optional>
#include "../Middleware/IRequestHandler.h"

#include "../RouteRegistrar/Router.h"

namespace beast=boost::beast;
namespace net=boost::asio;
namespace http=beast::http;

using tcp=net::ip::tcp;

class Session:public std::enable_shared_from_this<Session>{
    beast::tcp_stream m_stream;
    beast::flat_buffer m_buffer;
    http::request<http::string_body> m_request;
    std::optional<http::response<http::string_body>> m_response;
    //IRouter& m_router;
    IRequestHandler& m_requesthandler;
    void DoRead();
    void OnRead(beast::error_code ec,std::size_t size);
    void DoWrite();
    void OnWrite(beast::error_code ec,std::size_t size);
public:
    Session(tcp::socket&& socket,IRequestHandler& requestHandler);
    void run();
};