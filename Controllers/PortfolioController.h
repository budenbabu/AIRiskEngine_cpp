#pragma once

#include "IPortfolioController.h"
#include "../Service/IPortfolioService.h"
#include "../Common/http/HttpResponseFactory.h"
#include "../Models/Position.h"
#include "../Common/IJsonSerializer.h"
#include "../Validation/PositionValidator.h"
#include "../Loogger/ILogger.h"

class PortfolioController final: public IPortfolioController{
    IPortfolioService& m_service;
    HttpResponseFactory& m_resposeFactory;
    IJsonSerializer& m_serializer;
    IPositionValidator& m_validator;
    ILogger& m_loggger;
    
public:
    PortfolioController(IPortfolioService& service,HttpResponseFactory& factory,IJsonSerializer& serializer,
        IPositionValidator& validator,ILogger& loggger);
    http::response<http::string_body> GetPortfolio(const http::request<http::string_body>& request)override;
    http::response<http::string_body> CreatePortfolio(const http::request<http::string_body>& request)override;
    http::response<http::string_body> GetSummary(const http::request<http::string_body>& request)override;
    http::response<http::string_body> GetExposureSummary(const http::request<http::string_body>& request)override;
    http::response<http::string_body> GetPnLSummary(const http::request<http::string_body>& request)override;
    http::response<http::string_body> GetconcentrationSummary(const http::request<http::string_body>& request)override;
};