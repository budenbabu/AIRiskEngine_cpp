#include "WebSocketSessionFactory.h"
#include "WebSocketSession.h"

WebSocketSessionFactory::WebSocketSessionFactory(IWebSocketHub &hub, ILogger &logger)
    : m_hub(hub), m_logger(logger)
{
}

std::shared_ptr<IWebSocketSession> WebSocketSessionFactory::Create(boost::asio::ip::tcp::socket socket)
{
    return std::make_shared<WebSocketSession>(std::move(socket), m_hub, m_logger);
}
