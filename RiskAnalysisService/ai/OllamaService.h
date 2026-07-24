#pragma once

#include <boost\asio.hpp>
#include <boost\beast.hpp>
#include <ranges>

#include "../ai/PromptBuilder.h"
#include "../../Loogger/ILogger.h"
#include "IAIService.h"
#include "../../Common/IJsonSerializer.h"


namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using tcp = net::ip::tcp;
using json = nlohmann::json;

[[nodiscard]] constexpr bool iequals(std::string_view lhs, std::string_view rhs) noexcept {
    return std::ranges::equal(lhs, rhs, [](char a, char b) noexcept {
        return std::tolower(static_cast<unsigned char>(a)) == 
               std::tolower(static_cast<unsigned char>(b));
    });
}

class OllamaService : public IAIService {
	ILogger& m_logger;
	IJsonSerializer& m_serializer;
	int parse_severity(const nlohmann::json& j);
public:
	explicit OllamaService(ILogger& logger, IJsonSerializer& serializer);
	ns::AIAnalysisResult AnalysisRisk(const ns::RiskViolationEntity&) override;
};
