#pragma once

#include <boost\signals2.hpp>
#include "../PriceEvent/IMarketEvents.h"
#include "../../Service/IPortfolioService.h"


class PortfolioEventPublisher{
    boost::signals2::scoped_connection m_tradeConnection;
    boost::signals2::scoped_connection m_priceConnection;

    IMarketEvents& m_events;
    IPortfolioService& m_service;

    void Publish();
public:
    PortfolioEventPublisher(IMarketEvents& events,IPortfolioService& service);
};

