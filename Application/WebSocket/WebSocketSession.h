#pragma once

#include <boost/beast.hpp>
#include <iostream>
#include <memory>
#include <deque>
#include <sstream>

#include "../../Loogger/ILogger.h"
#include "IWebSocketSession.h"
#include "IWebSocketHub.h"

namespace beast = boost::beast;
namespace web = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class WebSocketSession :public IWebSocketSession, public std::enable_shared_from_this<WebSocketSession> {
	
	web::stream<beast::tcp_stream> m_ws;
	beast::flat_buffer m_buffer;
	IWebSocketHub& m_hub;
	std::deque<std::string> m_queue;
	ILogger& m_logger;

	void onAccept(beast::error_code ec);

	void DoRead();
	void onRead(beast::error_code ec,size_t bytes);

	void DoWrite();
	void onWrite(beast::error_code ec,size_t bytes);
	
	void Error(beast::error_code ec,const std::string msg);

	

public:
	WebSocketSession(tcp::socket&& socket, IWebSocketHub& hub,ILogger& logger);
	
	void Run()override;
	void Send(const std::string& msg) override;
	bool IsOpen() const override;
	void close() override;

};


