#pragma once
#include <string>
#include <nlohmann\json.hpp>

namespace ns{
    struct Quote
    {
        std::string symbol;
        double bid{};
        double ask{};
        double last{};
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Quote,symbol,bid,ask,last)
    };
}