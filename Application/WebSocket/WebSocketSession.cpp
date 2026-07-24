#include "WebSocketSession.h"

void WebSocketSession::onAccept(beast::error_code ec)
{
	if(ec){
		Error(ec,"WebSocketSession::onAccept");	
		return;
	}
	m_hub.Register(shared_from_this());
	m_logger.Info("Websocket client connection\n");
	DoRead();
}

void WebSocketSession::DoRead()
{
	m_ws.async_read(m_buffer,beast::bind_front_handler(&WebSocketSession::onRead,shared_from_this()));
}

void WebSocketSession::onRead(beast::error_code ec, size_t bytes)
{
	boost::ignore_unused(bytes);
	if(ec==web::error::closed){
		m_hub.Unregister(shared_from_this());

		Error(ec,"WebSocketSession::onRead");	
		return;
	}
	if(ec) Error(ec,"WebSocketSession::onRead");	
	m_buffer.consume(m_buffer.size());
	
}

void WebSocketSession::DoWrite()
{
	m_ws.async_write(net::buffer(m_queue.front()),beast::bind_front_handler(&WebSocketSession::onWrite,shared_from_this()));
}

void WebSocketSession::onWrite(beast::error_code ec,const size_t bytes){
	boost::ignore_unused(bytes);
	if(ec){
		Error(ec,"WebSocketSession::onWrite");
		return;
	}
	m_queue.pop_front();
	if(!m_queue.empty()) DoWrite();
}

void WebSocketSession::Error(beast::error_code ec, const std::string msg)
{
	std::ostringstream ss;
	ss<<msg<<ec.message();
	m_logger.Error(ss.str());
}

WebSocketSession::WebSocketSession(tcp::socket &&socket, IWebSocketHub &hub, ILogger &logger) : m_ws(std::move(socket)), m_hub(hub), m_logger(logger) {}

void WebSocketSession::Run()
{
	m_ws.set_option(web::stream_base::timeout::suggested(beast::role_type::server));
	m_ws.async_accept(beast::bind_front_handler(&WebSocketSession::onAccept,shared_from_this()));
}

void WebSocketSession::Send(const std::string& msg)
{
	bool write=!m_queue.empty();
	m_queue.push_back(msg);
	if(!write) DoWrite();
}

bool WebSocketSession::IsOpen() const
{
	return m_ws.is_open();
}

void WebSocketSession::close()
{	
	m_ws.async_close(web::close_code::normal);
}
