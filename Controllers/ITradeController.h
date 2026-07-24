#pragma once
#include "../pipeline/RequestContext.h"

class ITradeController{
public:
    virtual ~ITradeController()=default;
    virtual void ExecuteTrade(RequestContext& context)=0;
    virtual void GetTrades(RequestContext& context)=0;
    virtual void GetTradeById(RequestContext& context)=0;
    virtual void GetTradeBySymbol(RequestContext& context)=0;
};