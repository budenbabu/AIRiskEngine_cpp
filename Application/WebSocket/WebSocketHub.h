#pragma once


#include <sstream>
#include <shared_mutex>
#include <vector>
#include <ostream>
#include "../../Loogger/ILogger.h"
#include "IWebSocketHub.h"
#include "IWebSocketSession.h"

class WebSocketHub :public IWebSocketHub {
	mutable std::shared_mutex mtx;
	std::vector<std::shared_ptr<IWebSocketSession>> m_sessions;
	ILogger& m_logger;
public:	
	WebSocketHub(ILogger& logger);
	void Register(std::shared_ptr<IWebSocketSession> session) override;
	void Unregister(std::shared_ptr<IWebSocketSession> session) override;
	void Brodcast(const std::string& msg) override;
};