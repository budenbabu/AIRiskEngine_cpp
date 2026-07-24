#pragma once

#include "IMarketEvents.h"
#include "../PortfolioEvent/PortfolioUpdatedEvent.h"

class MarketEvents: public IMarketEvents 
{
    PriceUpdatedSignal m_psignal;
    TradeUpdatedSignal m_tsignal;
    PortfolioUpdatedSignal m_prosignal;
public:    
    MarketEvents();
    boost::signals2::connection SubscribePriceUpdate(const PriceUpdatedSignal::slot_type&)override;
    void publisherPriceUpdated(const PriceUpdatedEvent& event)override;

    boost::signals2::connection SubscribeTradeExecuted(const TradeUpdatedSignal::slot_type&)override;
    void PublishTradeExecuted(const ns::TradeExecutedEvent& event)override;

    boost::signals2::connection SubscribePortfolioUpdated(const PortfolioUpdatedSignal::slot_type&)override;
    void PublishPortfolioUpdated(const ns::PortfolioUpdatedEvent&)override;
};
