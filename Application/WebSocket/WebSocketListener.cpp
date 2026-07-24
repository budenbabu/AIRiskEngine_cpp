#include "WebSocketListener.h"
#include "IWebSocketSession.h"

void WebSocketListener::DoAccept()
{
    m_acceptor.async_accept(beast::bind_front_handler(&WebSocketListener::onAccept,this));
    std::cout << "[WebSocket] Client connected\n";
}

void WebSocketListener::onAccept(boost::system::error_code ec, tcp::socket socket)
{
    if(!ec){
        auto session=m_factory.Create(std::move(socket));
        session->Run();
    }
    std::cout << "[WebSocket] Handshake completed\n";
    DoAccept();
}

//WebSocketListener::WebSocketListener(net::io_context &ioc, unsigned short port, IWebSocketSessionFactory &factory) : m_acceptor(ioc, {tcp::v4(), port}), m_factory(factory) {}

void WebSocketListener::run(){ 
    DoAccept(); 
    std::cout << "WebSocket listener started\n";
}
