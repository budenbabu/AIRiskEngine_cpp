#include "PostgresNotificationListener.h"

PostgresNotificationListener::PostgresNotificationListener(DataBaseConfig& config, RiskRuleLoader& loader, ILogger& logger):
	m_conn(std::format("host={} port={} dbname={} user={} password={} hostaddr=127.0.0.1", config.m_host, config.m_port, config.m_database, config.m_user, config.m_password)),
	m_reciver(logger,std::ref(m_conn),loader){ 		
			m_thread = std::jthread([this](std::stop_token token) {Run(token); });
}

PostgresNotificationListener::~PostgresNotificationListener()
{
	m_thread.request_stop();
}


void PostgresNotificationListener::Run(std::stop_token token){
	while (!token.stop_requested()) {
		m_conn.await_notification();
	}
}