#pragma once
#include "../Infrastructure/PriceEvent/IMarketEvents.h"
#include "../Loogger/ILogger.h"




class PriceLogger
{
    ILogger& m_logger;
    void OnPriceUpdated(const PriceUpdatedEvent& e);
public:
    PriceLogger(IMarketEvents& event,ILogger& logger);
    ~PriceLogger();

};


