#include "RiskRuleController.h"

RiskRuleController::RiskRuleController(IRiskRuleRepository& repo, IJsonSerializer& serialize, HttpResponseFactory& factory, 
	IRiskViolationRepository& vrepo,ILogger& logger, IRiskAIAnalysisService& service)
	:m_factory(factory),m_logger(logger),m_repo(repo),m_serialize(serialize),m_vrepo(vrepo),m_service(service){
}

void RiskRuleController::getRules(RequestContext& context)
{
	auto& request = context.GetRequest();
	auto results = m_repo.GetAll();
	std::vector<ns::CreateRiskRuleRequest> cresult;
	cresult.reserve(results.size());
	for(auto& res : results){
		try{
			if (res) {			
				cresult.push_back({
					.rule_id = res->id,
					.ruleType = RiskRuleEntity::to_string(res->ruleType),
					.symbol = res->symbol.value_or(""),
					.value = res->value,
					.enabled = res->enabled,
					.description =res->description.value_or("")
				});
			}
		}catch(std::exception& ex){
			m_logger.Error(std::format("getRules: {}",ex.what()));
			throw std::runtime_error(ex.what());
		}
	}	
	context.setResponse(m_factory.OK(cresult, request));
}

void RiskRuleController::addRule(RequestContext& context)
{
	auto& request = context.GetRequest();
	auto rule = m_serialize.DeserializeObject<ns::CreateRiskRuleRequest>(request.body());
	m_repo.Add({
		.ruleType=RiskRuleEntity::from_string(rule.ruleType),
		.symbol=rule.symbol,
		.value=rule.value,
		.enabled=rule.enabled,
		.description=rule.description
	});
	context.setResponse(m_factory.OK(R"({"message":""Rule Added})",request));
	
}

void RiskRuleController::updatedRule(RequestContext& context)
{
	auto& request = context.GetRequest();	
	auto rule = m_serialize.DeserializeObject<ns::CreateRiskRuleRequest>(request.body());
	if(auto flag=m_repo.update({
		.id = rule.rule_id,
		.ruleType =RiskRuleEntity::from_string(rule.ruleType),
		.symbol = rule.symbol,
		.value = rule.value,
		.enabled = rule.enabled,
		.description = rule.description
	});!flag) { 
		ns::Messsage msg{.msg=std::format("unable to update rule rule id: {}",rule.rule_id)};
		context.setResponse(m_factory.BadRequest({m_serialize.SerializeObject<ns::Messsage>(msg)}, request)); 
		return;
	}
	context.setResponse(m_factory.OK(R"({"message":"Rule updated"})", request));
	
	
	
}

void RiskRuleController::deleteRule(RequestContext& context)
{
	auto& request = context.GetRequest();
	auto idstr = context.GetrouteValue("id");
	if (!idstr) {
		ns::Messsage msg = { .msg = "path value not found" };
		context.setResponse(m_factory.BadRequest({m_serialize.SerializeObject<ns::Messsage>(msg)}, request));
		return;
	}
	auto id = std::stoll(*context.GetrouteValue("id"));

	if (auto flag = m_repo.Delete(id); !flag) {		
		context.setResponse(m_factory.NotFound("Risk Rule not found", request));
		return;
	}
	else {
		ns::Messsage msg = { .msg = "Rule Deleted" };
		context.setResponse(m_factory.OK(msg,request));
	}
}

void RiskRuleController::riskViolation(RequestContext& context)
{
	auto& request = context.GetRequest();
	auto violiation = m_vrepo.GetAll();
	context.setResponse(m_factory.OK(violiation, request));
}

void RiskRuleController::riskViolationBySymbol(RequestContext& context)
{
	auto& request = context.GetRequest();
	auto symbol = context.GetrouteValue("symbol");
	if (!symbol) {
		ns::Messsage msg = { .msg = "path value not found" };
		context.setResponse(m_factory.BadRequest({ m_serialize.SerializeObject<ns::Messsage>(msg) }, request));
		return;
	}

	auto violations = m_vrepo.getBySymbol(*symbol);
	context.setResponse(m_factory.OK(violations, request));

}

void RiskRuleController::riskViolationByType(RequestContext& context)
{
	auto& request = context.GetRequest();
	auto symbol = context.GetrouteValue("type");
	if (!symbol) {
		ns::Messsage msg = { .msg = "path value not found" };
		context.setResponse(m_factory.BadRequest({ m_serialize.SerializeObject<ns::Messsage>(msg) }, request));
		return;
	}

	auto violations = m_vrepo.getByType(*symbol);
	context.setResponse(m_factory.OK(violations, request));
}

void RiskRuleController::GenerateAnalysis(RequestContext& context)
{
	auto& request = context.GetRequest();
	auto id = std::stoll(context.GetrouteValue("id").value_or(""));
 	m_service.Analysis(id);
	ns::Messsage ms = { .msg = "Analysis generated" };
	context.setResponse(m_factory.OK(ms, request));
}

//SELECT * FROM risk_violations WHERE trade_json-> > 'symbol' = 'TSLA'
