#pragma once
#include <boost/di.hpp>
#include <boost/beast/core.hpp>

#include "IWebSocketSessionFactory.h"

namespace net=boost::asio;
namespace beast=boost::beast;
using tcp=net::ip::tcp;

struct WSPort{};

class WebSocketListener{
    tcp::acceptor m_acceptor;
    IWebSocketSessionFactory& m_factory;

    void DoAccept();
    void onAccept(boost::system::error_code ec,tcp::socket socket);
public:
    //WebSocketListener(net::io_context& ioc,unsigned short port,IWebSocketSessionFactory& factory);
    BOOST_DI_INJECT(WebSocketListener,net::io_context& ioc,(named = WSPort{}) unsigned short port,IWebSocketSessionFactory& factory):
        m_acceptor(ioc,{tcp::v4(),port}),m_factory(factory){}
    void run();
};