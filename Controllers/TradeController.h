#pragma once
#include <format>
#include "ITradeController.h"
#include "../Common/http/HttpResponseFactory.h"
#include "../Common/IJsonSerializer.h"
#include "../Service/Trade/ITradeService.h"
#include "../Loogger/ILogger.h"
#include "../Domain/Trade/Trade.h"


class TradeController:public ITradeController{
    ILogger& m_logger;
    HttpResponseFactory& m_factor;
    IJsonSerializer& m_serialize;
    ITradeService& m_service;
public:
    TradeController(ILogger& logger,HttpResponseFactory& factor,IJsonSerializer& serialize,ITradeService& service);
    void ExecuteTrade(RequestContext& context)override;
    void GetTrades(RequestContext& context)override;    
    void GetTradeById(RequestContext& context)override;
    void GetTradeBySymbol(RequestContext& context)override;
};