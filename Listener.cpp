#include "Listener.h"

Listener::Listener(net::io_context &ioc, unsigned short port, ISessionFactory &factory):m_acceptor(ioc),m_factory(factory)
{
    beast::error_code ec;
    tcp::endpoint endpoint{tcp::v4(),port};
    m_acceptor.open(endpoint.protocol(),ec);
    if(ec) ThrowIfError(ec,"acceptor.open");
    m_acceptor.set_option(net::socket_base::reuse_address(true),ec);
    if(ec) ThrowIfError(ec,"acceptor.set_option");
    m_acceptor.bind(endpoint,ec);
    if(ec) ThrowIfError(ec,"acceptor.bind");
    m_acceptor.listen(net::socket_base::max_listen_connections,ec);
    if(ec) ThrowIfError(ec,"acceptor.listen");
}

void Listener::Run()
{
    DoAccept();
}

void Listener::Stop(){
    beast::error_code ec;
    if (m_acceptor.is_open()) {
        m_acceptor.cancel(ec);
        m_acceptor.close(ec);
    }
}

void Listener::DoAccept(){
    m_acceptor.async_accept(beast::bind_front_handler(&Listener::OnAccept,shared_from_this()));
}

void Listener::OnAccept(error_code ec,tcp::socket socket){
    if(ec){
        if(ec == net::error::operation_aborted) {
            return;
        }
        std::cout<<"Error: "<<ec.message()<<"\n";
        return;
    }

    std::cout<<"Client connected\n";
    auto session=m_factory.Create(std::move(socket));
    session->run();
    DoAccept();
}
