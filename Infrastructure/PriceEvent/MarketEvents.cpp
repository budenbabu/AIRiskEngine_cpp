#include "MarketEvents.h"

MarketEvents::MarketEvents()
{
}

boost::signals2::connection MarketEvents::SubscribePriceUpdate(const PriceUpdatedSignal::slot_type &slot)
{
    return m_psignal.connect(slot);
}

void MarketEvents::publisherPriceUpdated(const PriceUpdatedEvent &event)
{
    m_psignal(event);
}

boost::signals2::connection MarketEvents::SubscribeTradeExecuted(const TradeUpdatedSignal::slot_type& slot)
{
    return m_tsignal.connect(slot);
}

void MarketEvents::PublishTradeExecuted(const ns::TradeExecutedEvent &event)
{
    m_tsignal(event);
}

boost::signals2::connection MarketEvents::SubscribePortfolioUpdated(const PortfolioUpdatedSignal::slot_type& slot)
{
    return m_prosignal.connect(slot);
}

void MarketEvents::PublishPortfolioUpdated(const ns::PortfolioUpdatedEvent& event)
{
    m_prosignal(event);
}
