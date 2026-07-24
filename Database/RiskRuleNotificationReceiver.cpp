#include "RiskRuleNotificationReceiver.h"
#include <boost/core/ignore_unused.hpp>

RiskRuleNotificationReceiver::RiskRuleNotificationReceiver(ILogger& logger, pqxx::connection& conn, RiskRuleLoader& loader):
	pqxx::notification_receiver(conn, "risk_rule_updates"),m_loader(loader),m_logger(logger)
{
	if (!conn.is_open())
		m_logger.Error("Connection lost");
}

void RiskRuleNotificationReceiver::operator()(std::string const& payload, int backend_pid)
{
	m_logger.Info(std::format("Notification recived: {}", payload));
	m_loader.ReLoad();
	boost::ignore_unused(backend_pid);
}
