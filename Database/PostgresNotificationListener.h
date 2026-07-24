#pragma once

#include <thread>
#include <pqxx/pqxx>

#include "RiskRuleNotificationReceiver.h"
#include "DatabaseConfig.h"

class PostgresNotificationListener {
	pqxx::connection m_conn;
	RiskRuleNotificationReceiver m_reciver;
	std::jthread m_thread;
	void Run(std::stop_token token);
public:
	PostgresNotificationListener(DataBaseConfig& config, RiskRuleLoader& loader, ILogger& logger);
	~PostgresNotificationListener();
};
