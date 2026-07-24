#include "PriceLogger.h"

void PriceLogger::OnPriceUpdated(const PriceUpdatedEvent& e)
{
	std::ostringstream ss;
	ss << "[Event] " << e.quote.symbol << " " << e.quote.last << '\n';
	//m_logger.Info(ss.str());
}

PriceLogger::PriceLogger(IMarketEvents& event, ILogger& logger):m_logger(logger)
{
	event.SubscribePriceUpdate([this](const PriceUpdatedEvent& e) {
		OnPriceUpdated(e);
	});
}

PriceLogger::~PriceLogger(){}
