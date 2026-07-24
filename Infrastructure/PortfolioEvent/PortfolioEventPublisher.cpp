#include "PortfolioEventPublisher.h"

void PortfolioEventPublisher::Publish()
{
    m_events.PublishPortfolioUpdated({
        .pnl=m_service.GetPnLSummary(),
        .exposure=m_service.GetExposureSummary(), 
        .concenration=m_service.GetconcentrationSummary()
    });
}

PortfolioEventPublisher::PortfolioEventPublisher(IMarketEvents &events, IPortfolioService &service):m_events(events),m_service(service)
{
    m_tradeConnection=events.SubscribeTradeExecuted([this](const auto&){ Publish(); });
    m_priceConnection=events.SubscribePriceUpdate([this](const auto&){ Publish(); });
}