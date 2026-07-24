#pragma once
#include <boost\core\ignore_unused.hpp>
#include <format>
#include "../Service/IPortfolioService.h"
#include "IRiskRule.h"

class MaxTradeQuantityRule:public IRiskRule{
    double m_limit;    
public:
    explicit MaxTradeQuantityRule(double limit);
    ns::RiskResult Validate(const ns::Trade trade,const std::optional<ns::Position>& position)const override;
};


class MaxPositionRule:public IRiskRule{
    double m_maxPosition;
    std::string m_symbol;
public:
    explicit MaxPositionRule(double maxPosition,std::string symbol);
    ns::RiskResult Validate(const ns::Trade trade,const std::optional<ns::Position>& position)const override;
};

class MaxExposureRule : public IRiskRule{
    double m_maxRxposure;
public:
    explicit MaxExposureRule(double maxRxposure);
    ns::RiskResult Validate(const ns::Trade trade,const std::optional<ns::Position>& position)const override;
};


class DailyLossRule:public IRiskRule{
    IPortfolioService& m_service;
    double m_dailyLossLimit;
public:
    explicit DailyLossRule(double dailyLossLimit,IPortfolioService& service);
    ns::RiskResult Validate(const ns::Trade trade,const std::optional<ns::Position>& position)const override;
};