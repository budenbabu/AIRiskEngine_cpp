#pragma once

#include <boost\signals2.hpp>
#include "../../Repository/IPortfolioRepository.h"
#include "../../Infrastructure/PriceEvent/MarketEvents.h"
#include "../../Loogger/ILogger.h"


class PortfolioPriceUpdater
{
	IPortfolioRepository& m_repository;
	boost::signals2::scoped_connection m_connection;
	ILogger& m_logger;
	void onPriceUpdated(const PriceUpdatedEvent& event);
public:
	PortfolioPriceUpdater(IMarketEvents& event, IPortfolioRepository& m_repository,ILogger& logger);
};
