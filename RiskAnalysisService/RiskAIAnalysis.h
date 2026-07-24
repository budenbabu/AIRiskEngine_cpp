#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <chrono>


struct RiskAIAnalysisEntity
{
    std::uint64_t analysisId{};
    std::uint64_t violationId{};
    std::string analysis;
    std::string recommendation;
    std::string modelName;    
    double confidence{};
    double severity{};
    std::string createdAt;
};


namespace ns{    
    struct RiskAIAnalysisEntityDto : public RiskAIAnalysisEntity {};
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        RiskAIAnalysisEntityDto, 
        analysisId, 
        violationId, 
        analysis, 
        recommendation, 
        modelName, 
        confidence, 
        severity, 
        createdAt
    )
}


namespace ns {
    struct Request {
        std::string model;
        std::string prompt;
        bool stream{false};
        std::string format;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Request, model, prompt, stream,format)
    };

    struct AIAnalysisResult
    {
        std::string analysis;
        std::string recommendation;
        std::string model;
        double severity{};
        double confidence{};
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AIAnalysisResult, analysis, recommendation, model, severity, confidence)
    };
}

namespace ns {
    enum class AIJobStatus
    {
        Pending,
        Processing,
        Completed,
        Failed
    };
    inline std::string ToString(AIJobStatus s)
    {
        switch (s)
        {
        case AIJobStatus::Pending:
            return "PENDING";

        case AIJobStatus::Processing:
            return "PROCESSING";

        case AIJobStatus::Completed:
            return "COMPLETED";

        case AIJobStatus::Failed:
            return "FAILED";
        }

        return "UNKNOWN";
    }
    inline AIJobStatus FromString(
            const std::string& status)
    {
        if (status == "PENDING")
            return AIJobStatus::Pending;

        if (status == "PROCESSING")
            return AIJobStatus::Processing;

        if (status == "COMPLETED")
            return AIJobStatus::Completed;

        if (status == "FAILED")
            return AIJobStatus::Failed;

        throw std::runtime_error(
            "Unknown AI job status: "
            + status);
    }
    struct AIJob
    {
        uint64_t jobID{};
        uint64_t violationId{};
        AIJobStatus status{ AIJobStatus::Pending };
        int retryCount{};
        std::string errorMsg;
        std::string cretedAt;
        std::string startedAt;
        std::string completedAt;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AIJob, violationId, status,retryCount, errorMsg, cretedAt, startedAt, completedAt)        
    };

    struct AIAnalysis
    {
        uint64_t analysisId{};
        uint64_t jobId{};
        uint64_t violationId{};
        std::string modelName;
        std::string analysisJson;
        std::uint64_t processingTimeMs{};
        std::string createdAt;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AIAnalysis, analysisId, jobId,violationId, modelName, analysisJson, processingTimeMs,createdAt)        
    };
}



struct AIJobDto
{
    uint64_t jobID{};
    uint64_t violationId{};
    std::string status = ns::ToString(ns::AIJobStatus::Pending);
    int retryCount{};
    std::string errorMsg;
    std::chrono::system_clock::time_point cretedAt;
    std::optional<std::chrono::system_clock::time_point> startedAt;
    std::optional<std::chrono::system_clock::time_point> completedAt;
};

struct AIQueueItem {
    uint64_t violationId{};
    uint64_t jobid{};
};