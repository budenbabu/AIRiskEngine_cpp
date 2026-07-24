#pragma once

#include <atomic>
#include <format>
#include <boost/asio.hpp>
#include "../../Loogger/ILogger.h"

class AIExecutor {
	boost::asio::thread_pool m_pool;
	std::atomic_uint64_t m_pending{};
	ILogger& m_logger;
public:
	explicit AIExecutor(std::size_t threads,ILogger& logger);
	~AIExecutor();
	template<typename Fn>
	void Post(Fn&& fn) {
		//boost::asio::post(m_pool, std::forward<Fn>(fn));	
		auto pending=++m_pending;
		m_logger.Info(std::format("AI queue. pending={}",pending));
		boost::asio::post(m_pool,[this,task=std::forward<Fn>(fn)]{
			//auto tid=std::this_thread::get_id();			
			task();
			auto left=--m_pending;
			m_logger.Info(std::format("AI completed. pending={}",left));
		});
		
	}
};
