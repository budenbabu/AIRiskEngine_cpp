#pragma once

#include <boost\asio.hpp>
#include <boost\beast\core.hpp>
#include <boost\di.hpp>
#include <iostream>
#include "Sessions\\Session.h"
#include "Sessions\\ISessionFactory.h"
//#include <enable_shared_from_this.hpp>
#include <memory>

namespace net=boost::asio;
namespace beast=boost::beast;
using tcp=net::ip::tcp;

using error_code=boost::system::error_code;

class Listener: public std::enable_shared_from_this<Listener>{
    tcp::acceptor m_acceptor;    
    ISessionFactory& m_factory;
public:
    //  BOOST_DI_INJECT(Listener,net::io_context& ioc,(named = ServerPort{}) unsigned short port,ISessionFactory& factory):
    //      m_acceptor(ioc),m_factory(factory){
    //           beast::error_code ec;
    //           tcp::endpoint endpoint{tcp::v4(),port};
    //           m_acceptor.open(endpoint.protocol(),ec);
    //           if(ec) ThrowIfError(ec,"acceptor.open");
    //           m_acceptor.set_option(net::socket_base::reuse_address(true),ec);
    //           if(ec) ThrowIfError(ec,"acceptor.set_option");
    //           m_acceptor.bind(endpoint,ec);
    //           if(ec) ThrowIfError(ec,"acceptor.bind");
    //           m_acceptor.listen(net::socket_base::max_listen_connections,ec);
    //           if(ec) ThrowIfError(ec,"acceptor.listen");
    //  }
    Listener(net::io_context& io,unsigned short port,ISessionFactory& factory);
    void Run();
    void Stop();

private:
    void DoAccept();
    void OnAccept(error_code ec,tcp::socket scoket);
    inline void ThrowIfError(beast::error_code ec,std::string_view operation)
    {
        if (ec)
        {
            throw beast::system_error(ec,std::string(operation));
        }
    }
};

//Listener::Listener(net::io_context& ioc,tcp::endpoint endpoint,ISessionFactory& factory):m_acceptor(ioc),m_factory(factory){
//    beast::error_code ec;
//    m_acceptor.open(endpoint.protocol(),ec);
//    if(ec) ThrowIfError(ec,"acceptor.open");
//    m_acceptor.set_option(net::socket_base::reuse_address(true),ec);
//    if(ec) ThrowIfError(ec,"acceptor.set_option");
//    m_acceptor.bind(endpoint,ec);
//    if(ec) ThrowIfError(ec,"acceptor.bind");
//    m_acceptor.listen(net::socket_base::max_listen_connections,ec);
//    if(ec) ThrowIfError(ec,"acceptor.listen");
//}
