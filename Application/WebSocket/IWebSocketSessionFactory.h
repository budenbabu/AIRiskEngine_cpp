#pragma once

#include<boost/asio.hpp>
#include <memory>
class IWebSocketSession;

class IWebSocketSessionFactory{
public:
    virtual ~IWebSocketSessionFactory()=default;
    virtual std::shared_ptr<IWebSocketSession> Create(boost::asio::ip::tcp::socket socket)=0;
};