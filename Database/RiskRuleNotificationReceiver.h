#pragma once

#include <pqxx\pqxx>
#include <string_view>

#include "../Loogger/ILogger.h"
#include "../RiskRule/RiskRuleLoader.h"

class PostgreSqlConnectionPool;

class RiskRuleNotificationReceiver : public pqxx::notification_receiver {
	ILogger& m_logger;	
	RiskRuleLoader& m_loader;	
public:		
	RiskRuleNotificationReceiver(ILogger& logger, pqxx::connection& m_conn, RiskRuleLoader& loader);
	void operator()(std::string const& payload, int backend_pid)override;
};