#pragma once

#include "IWebSocketHub.h"
#include "IWebSocketSessionFactory.h"
#include "IWebSocketSession.h"

class ILogger;

class WebSocketSessionFactory : public IWebSocketSessionFactory {
    IWebSocketHub& m_hub;
    ILogger& m_logger;
public:
    WebSocketSessionFactory(IWebSocketHub& hub, ILogger& logger);
    std::shared_ptr<IWebSocketSession> Create(boost::asio::ip::tcp::socket socket)override;
};