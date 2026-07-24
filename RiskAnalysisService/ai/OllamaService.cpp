#include "OllamaService.h"

int OllamaService::parse_severity(const nlohmann::json &j)
{
    int severity=1;
    // Early Exit pattern: If the property isn't there, default and leave immediately.
    if (!j.contains("severity")) {
        severity = 1;
        return severity;
    }

    const auto& sev = j["severity"];

    if (sev.is_number_integer()) {
        severity = sev.get<int>();
        return severity;
    }

    if (sev.is_number_float()) {
        // Explicitly narrow the double down to avoid any variant warnings
        severity = static_cast<int>(std::round(sev.get<double>()));
        return severity;
    }

    if (sev.is_string()) {
        // Extract as string_view to avoid copying characters out of the JSON tree buffer
        const auto value = sev.get<std::string_view>();

        if (iequals(value, "low")) {
            severity = 1;
        } else if (iequals(value, "medium") || iequals(value, "moderate")) {
            severity = 2;
        } else if (iequals(value, "high")) {
            severity = 3;
        } else if (iequals(value, "critical")) {
            severity = 4;
        } else {
            severity = 1; // Unknown string fallback
        }
        return severity;
    }

    // Fallback if the type is unexpected (e.g., bool or null arrays)
    severity = 1;
    return severity;
}


OllamaService::OllamaService(ILogger &logger, IJsonSerializer &serializer) : m_logger(logger), m_serializer(serializer) {}

ns::AIAnalysisResult OllamaService::AnalysisRisk(const ns::RiskViolationEntity& violation)
{
    try {
        auto prompt = PromptBuilder::BuildRiskAnalysisPrompt(violation);
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);
        stream.expires_after(std::chrono::seconds(15));
        auto endpoint = resolver.resolve("localhost", "11434");
        stream.connect(endpoint);
        ns::Request req = {
            .model = "qwen2.5:3b",
            .prompt = prompt,
            .stream = false,
            .format = "json"

        };
        auto body = m_serializer.SerializeObject<ns::Request>(req);

        http::request<http::string_body> request{ http::verb::post, "/api/generate",11 };
        request.set(http::field::host, "localhost");
        request.body() = body;
        request.prepare_payload();
        http::write(stream, request);
        beast::flat_buffer buffer;
        http::response<http::string_body> response;
        http::read(stream, buffer, response);
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);
        if (response.result() != http::status::ok) {
            auto estr = std::move(std::format("Ollama returned status {}", static_cast<int>(response.result())));
            m_logger.Error(estr);
            throw std::runtime_error(estr);
        }
        json outer_json = json::parse(response.body());
        std::string inner_json_string = outer_json["response"].get<std::string>();
        m_logger.Info(inner_json_string);
        ns::AIAnalysisResult result = {};
        json j = json::parse(inner_json_string);
        result.analysis = j.value("analysis", "");
        result.recommendation = j.value("recommendation", "");
        result.model = j.value("model", "llama3.2");
        result.severity = parse_severity(j);

        // auto result = m_serializer.DeserializeObject<ns::AIAnalysisResult>(inner_json_string);
        return result;
    }
    catch (const std::exception& ex) {
        auto estr = std::move(std::format("Ollama returned status {}", ex.what()));
        m_logger.Error(estr);
        throw std::runtime_error(estr);
    }
}
