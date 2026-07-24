#pragma once

#include <nlohmann\json.hpp>
#include <string>

namespace ns{
    enum class RiskViolation{ None, MaxTradeQuantity, MaxPosition, MaxExposure, DailyLoss};

    NLOHMANN_JSON_SERIALIZE_ENUM(RiskViolation, {
        {RiskViolation::None, "None"},
        {RiskViolation::MaxTradeQuantity, "MaxTradeQuantity"},
        {RiskViolation::MaxPosition, "MaxPosition"},
        {RiskViolation::MaxExposure, "MaxExposure"},
        {RiskViolation::DailyLoss, "DailyLoss"}
    })

    struct RiskResult{
        bool allowed{true};
        std::string reason;
        RiskViolation violation{RiskViolation::None};
        explicit operator bool ()const{ return allowed;}
        static RiskResult Allow(){ return {}; }
        static RiskResult Reject(std::string reason,RiskViolation violation){
            return { false, std::move(reason), violation};
        }
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RiskResult,allowed,reason,violation)
    };

    

    struct CreateRiskRuleRequest
    {
        std::uint64_t rule_id{};
        std::string ruleType;
        std::string symbol;
        double value{};
        bool enabled{ true };
        std::string description;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CreateRiskRuleRequest,rule_id,ruleType, symbol, value, enabled, description)
    };


    struct Messsage {
        std::string msg;   
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Messsage, msg)
    };
}

namespace ns{
    struct RiskViolationEntity
    {
        std::uint64_t id{};
        std::uint64_t timestamp{};
        std::string symbol;
        ns::RiskViolation violation;
        std::string message;
        std::string tradeJson;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RiskViolationEntity, id,timestamp,symbol,violation,message,tradeJson)
    };
}

struct RiskRuleEntity
{
        std::uint64_t id{};
        ns::RiskViolation ruleType;
        std::optional<std::string> symbol;
        double value{};
        bool enabled{};
        std::optional<std::string> description;

        std::string static to_string(ns::RiskViolation violation) {
        switch (violation) {
        case ns::RiskViolation::None:             return "None";
        case ns::RiskViolation::MaxTradeQuantity: return "MaxTradeQuantity";
        case ns::RiskViolation::MaxPosition:      return "MaxPosition";
        case ns::RiskViolation::MaxExposure:      return "MaxExposure";
        case ns::RiskViolation::DailyLoss:        return "DailyLoss";
        default:                                    return "Unknown";
        }
    }

    ns::RiskViolation static from_string(std::string_view str) {
        if (str == "None")             return ns::RiskViolation::None;
        if (str == "MaxTradeQuantity") return ns::RiskViolation::MaxTradeQuantity;
        if (str == "MaxPosition")      return ns::RiskViolation::MaxPosition;
        if (str == "MaxExposure")      return ns::RiskViolation::MaxExposure;
        if (str == "DailyLoss")        return ns::RiskViolation::DailyLoss;
        throw std::invalid_argument("Invalid RiskViolation string: " + std::string(str));
    }
};

