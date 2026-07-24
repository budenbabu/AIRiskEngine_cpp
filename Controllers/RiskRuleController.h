#pragma once
#include "../Repository/Risk/IRiskRuleRepository.h"
#include "../Common/IJsonSerializer.h"
#include "../Common/http/HttpResponseFactory.h"
#include "../Loogger/ILogger.h"
#include "IRiskRuleController.h"
#include "../Repository/Risk/Violation/IRiskViolationRepository.h"
#include "../RiskAnalysisService/Services/IRiskAIAnalysisService.h"


class RiskRuleController:public IRiskRuleController
{
	IRiskRuleRepository& m_repo;
	IRiskViolationRepository& m_vrepo;
	HttpResponseFactory& m_factory;
	IJsonSerializer& m_serialize;
	IRiskAIAnalysisService& m_service;
	ILogger& m_logger;

public:
	RiskRuleController(IRiskRuleRepository& repo, IJsonSerializer& serialize, HttpResponseFactory& factory,
		IRiskViolationRepository& m_vrepo ,ILogger& logger, IRiskAIAnalysisService& service);

	// Inherited via IRiskRuleController
	void getRules(RequestContext& context) override;
	void addRule(RequestContext& context) override;
	void updatedRule(RequestContext& context) override;
	void deleteRule(RequestContext& context) override;

	void riskViolation(RequestContext& context) override;
	void riskViolationBySymbol(RequestContext& context) override;
	void riskViolationByType(RequestContext& context) override;

	void GenerateAnalysis(RequestContext& context)override;
};
