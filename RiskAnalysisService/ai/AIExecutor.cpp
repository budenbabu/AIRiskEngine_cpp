#include "AIExecutor.h"

AIExecutor::AIExecutor(std::size_t threads,ILogger& logger):m_logger(logger),m_pool(threads){
	m_logger.Info(std::format("AIExecutor NO thread {}",threads));
}

AIExecutor::~AIExecutor()
{
	m_pool.join();
}
