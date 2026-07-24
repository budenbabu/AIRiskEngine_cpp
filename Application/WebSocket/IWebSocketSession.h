#pragma once

#include <string>
#include <iostream>



class IWebSocketSession {
public:
	virtual ~IWebSocketSession() = default;
	virtual void Send(const std::string& msg) = 0;
	virtual void Run() = 0;
	virtual bool IsOpen()const = 0;
	virtual void close() = 0;
};

//class FackWebSocketSession: public IWebSocketSession {
//public:
//	void Send(const std::string& msg) override {
//		std::cout << "[Fake client] " << msg << '\n';
//	}
//
//
//	// Inherited via IWebSocketSession
//	bool IsOpen() const override {
//		std::cout << "Is open\n";
//	}
//
//	void close() override {
//		std::cout << "Closed\n";
//	}
//
//};