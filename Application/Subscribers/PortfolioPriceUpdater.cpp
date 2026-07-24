#include "PortfolioPriceUpdater.h"

void PortfolioPriceUpdater::onPriceUpdated(const PriceUpdatedEvent& event)
{
	auto updated=m_repository.UpdateMarketPrice(event.quote.symbol,event.quote.last);
	if(updated){
		std::ostringstream oss;
		oss<< "[Portfolio] "<< event.quote.symbol<< " updated to "<< event.quote.last<< '\n';
		//m_logger.Info(oss.str());
	}

}

PortfolioPriceUpdater::PortfolioPriceUpdater(IMarketEvents& event, IPortfolioRepository& repository,ILogger& logger):
	m_repository(repository),m_logger(logger){
	m_connection = event.SubscribePriceUpdate([this](const PriceUpdatedEvent& e) {
		onPriceUpdated(e);
	});
}
