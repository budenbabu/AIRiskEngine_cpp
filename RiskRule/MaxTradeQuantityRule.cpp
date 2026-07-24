#include "MaxTradeQuantityRule.h"

MaxTradeQuantityRule::MaxTradeQuantityRule(double limit):m_limit(limit){}

ns::RiskResult MaxTradeQuantityRule::Validate(const ns::Trade trade, const std::optional<ns::Position> &position) const
{
    boost::ignore_unused(position);
    if(trade.quantity > m_limit)
        return ns::RiskResult::Reject(std::format("Trade quantity exceeds limit {}",m_limit),ns::RiskViolation::MaxTradeQuantity);
    return ns::RiskResult::Allow();
}

MaxPositionRule::MaxPositionRule(double maxPosition,std::string symbol):m_maxPosition(maxPosition),m_symbol(std::move(symbol)){}

ns::RiskResult MaxPositionRule::Validate(const ns::Trade trade, const std::optional<ns::Position> &position) const
{
    std::int64_t currentQty=position?position->quantity:0;
    std::int64_t newQty=currentQty;
    if(trade.side==ns::TradeSize::BUY) newQty+=trade.quantity;
    else newQty-=trade.quantity;
    if(newQty>m_maxPosition)
        return ns::RiskResult::Reject(
            std::format("Position limit exceded "
            "Symbol= {} Current= {} Requested= {} Limit= {}",trade.symbol,currentQty,trade.quantity,m_maxPosition)
            ,ns::RiskViolation::MaxPosition);
    return ns::RiskResult::Allow();
}

MaxExposureRule::MaxExposureRule(double maxRxposure):m_maxRxposure(maxRxposure){}

ns::RiskResult MaxExposureRule::Validate(const ns::Trade trade, const std::optional<ns::Position> &position) const
{
    std::int64_t quantity=position?position->quantity:0;
    if(trade.side==ns::TradeSize::BUY) quantity+=trade.quantity;
    else quantity-=trade.quantity;
    auto exposure=static_cast<double>(quantity)*trade.price;
    if(exposure > m_maxRxposure)
        return ns::RiskResult::Reject(
            std::format("Exposure limit exceeded "
            "Symbol= {} Expouse= {} Limit= {}",trade.symbol,exposure,m_maxRxposure)
            ,ns::RiskViolation::MaxExposure);

    return ns::RiskResult::Allow();
}

DailyLossRule::DailyLossRule(double dailyLossLimit,IPortfolioService& service):m_dailyLossLimit(dailyLossLimit),m_service(service){}

ns::RiskResult DailyLossRule::Validate(const ns::Trade trade, const std::optional<ns::Position> &position) const
{

    auto pnl=m_service.GetPnLSummary();
    if(pnl.totalRealizedPnl <= -m_dailyLossLimit)
        return ns::RiskResult::Reject(
            std::format("Daily loss limit exceded "
            "PnL= {} Limit= {}",pnl.totalRealizedPnl,m_dailyLossLimit)
            ,ns::RiskViolation::DailyLoss);
    boost::ignore_unused(trade);
    boost::ignore_unused(position);
    return ns::RiskResult::Allow();
}
