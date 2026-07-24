#pragma once

#include <boost\asio.hpp>
#include <memory>

class Session;
using tcp=boost::asio::ip::tcp;

class ISessionFactory{
public:
    virtual ~ISessionFactory()=default;
    virtual std::shared_ptr<Session> Create(tcp::socket&& socket)=0;
};