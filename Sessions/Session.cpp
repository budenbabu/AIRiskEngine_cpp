#include "Session.h"

void Session::DoRead()
{
    m_request={};
    m_stream.expires_after(std::chrono::seconds(30));
    http::async_read(m_stream,m_buffer,m_request,beast::bind_front_handler(&Session::OnRead,shared_from_this()));
    
}

void Session::OnRead(beast::error_code ec, std::size_t size)
{
    boost::ignore_unused(size);
    if(ec==http::error::end_of_stream){
        beast::error_code shutdownEc;
        m_stream.socket().shutdown(tcp::socket::shutdown_send,shutdownEc);
        return;
    }
    if(ec){ 
        if(ec == boost::asio::error::operation_aborted) {
            return;
        }
        std::cout<<"Error: "<<ec.message()<<'\n';
        return;
    }
    if(ec==http::error::end_of_stream){
        beast::error_code sh;
        m_stream.socket().shutdown(tcp::socket::shutdown_send,sh);
        return;
    }
    std::cout<<m_request.method_string()<<" "<<m_request.target()<<"\n";
    RequestContext context(std::move(m_request));
    m_requesthandler.Handler(context);
    m_response=std::move(context.GetResponse());
    DoWrite();
}

void Session::DoWrite()
{
    m_stream.expires_after(std::chrono::seconds(30));
    http::async_write(m_stream,*m_response,beast::bind_front_handler(&Session::OnWrite,shared_from_this()));
}

void Session::OnWrite(beast::error_code ec, std::size_t size)
{
    boost::ignore_unused(size);
    if(ec){
        if(ec == boost::asio::error::operation_aborted) {
            return;
        }
        std::cout<<"Error: "<<ec.message()<<'\n';
        return;
    }
    if(m_response->need_eof()){
        beast::error_code shutdownEc;
        m_stream.socket().shutdown(tcp::socket::shutdown_send,shutdownEc);
        return;
    }
    m_response.reset();
    DoRead();
}

Session::Session(tcp::socket &&socket, IRequestHandler& router) :
     m_stream(std::move(socket)), m_requesthandler(router){}

void Session::run()
{
    DoRead();
}
