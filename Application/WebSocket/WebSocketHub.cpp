#include "WebSocketHub.h"

WebSocketHub::WebSocketHub(ILogger& logger):m_logger(logger)
{
}

void WebSocketHub::Register(std::shared_ptr<IWebSocketSession> session)
{
	std::unique_lock lock(mtx);
	m_sessions.push_back(session);
	std::ostringstream oss;
	oss << "[Hub] Client connected. Total = "<< m_sessions.size()<< '\n';
	m_logger.Info(oss.str());
	
}

void WebSocketHub::Unregister(std::shared_ptr<IWebSocketSession> session)
{
	std::unique_lock lock(mtx);
	auto it = std::remove(m_sessions.begin(), m_sessions.end(), session);
	m_sessions.erase(it, m_sessions.end());
	std::ostringstream oss;
	oss << "[Hub] Client disconnected. Total = " << m_sessions.size() << '\n';
	m_logger.Info(oss.str());
}

void WebSocketHub::Brodcast(const std::string& msg)
{
	std::shared_lock lock(mtx);
	for (const auto& it : m_sessions)		
		it->Send(msg);
}
