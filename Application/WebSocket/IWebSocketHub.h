#pragma once

#include <string>
#include <memory>

class IWebSocketSession;

class IWebSocketHub {
public:
	virtual ~IWebSocketHub() = default;
	virtual void Register(std::shared_ptr<IWebSocketSession> session) = 0;
	virtual void Unregister(std::shared_ptr<IWebSocketSession> session) = 0;
	virtual void Brodcast(const std::string& msg) = 0;
};
