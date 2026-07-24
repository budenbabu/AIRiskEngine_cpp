#pragma once

#include <boost/signals2.hpp>
#include "PriceUpdatedEvent.h"
#include "../TradeEvent/TradeExecutedEvent.h"
#include "../PortfolioEvent/PortfolioUpdatedEvent.h"


class IMarketEvents{
public:
    using PriceUpdatedSignal=boost::signals2::signal<void(const PriceUpdatedEvent&)>;
    using TradeUpdatedSignal=boost::signals2::signal<void(const ns::TradeExecutedEvent&)>;
    using PortfolioUpdatedSignal = boost::signals2::signal<void(const ns::PortfolioUpdatedEvent&)>;

    virtual ~IMarketEvents()=default;
    virtual boost::signals2::connection SubscribePriceUpdate(const PriceUpdatedSignal::slot_type&)=0;
    virtual void publisherPriceUpdated(const PriceUpdatedEvent& event)=0;

    
    virtual boost::signals2::connection SubscribeTradeExecuted(const TradeUpdatedSignal::slot_type&)=0;
    virtual void PublishTradeExecuted(const ns::TradeExecutedEvent& event)=0;

    virtual boost::signals2::connection SubscribePortfolioUpdated(const PortfolioUpdatedSignal::slot_type&) = 0;
    virtual void PublishPortfolioUpdated(const ns::PortfolioUpdatedEvent&) = 0;
};