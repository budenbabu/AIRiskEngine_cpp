#include "AIAnalysisController.h"

AIAnalysisController::AIAnalysisController(AIAnalysisService &service,HttpResponseFactory& factory ,ILogger &logger):
    m_service(service),m_logger(logger),m_factory(factory){}

void AIAnalysisController::getAll(RequestContext &context)
{
    auto& request=context.GetRequest();
    auto results=m_service.GetAll();    
    std::vector<ns::RiskAIAnalysisEntityDto> dtos(std::make_move_iterator(results.begin()),std::make_move_iterator(results.end()));
    context.setResponse(m_factory.OK(dtos,request));
}

void AIAnalysisController::getByVid(RequestContext& context)
{
    auto& request=context.GetRequest();
    auto svid=context.GetrouteValue("vid");
    if(!svid){        
        context.setResponse(m_factory.BadRequest({"violation id is invaild"},request));
        return;
    }

    auto vid=std::stoll(*svid);
    auto result=m_service.getByViolationID(vid);
    if(!result){
        context.setResponse(m_factory.BadRequest({std::format("violation id not found {}",vid)},request));
        return;
    }
    ns::RiskAIAnalysisEntityDto temp={std::move(*result)};
    context.setResponse(m_factory.OK(temp,request));
}

void AIAnalysisController::getByAid(RequestContext& context)
{
    auto& request=context.GetRequest();
    auto said=context.GetrouteValue("aid");
    if(!said){        
        context.setResponse(m_factory.BadRequest({"violation id is invaild"},request));
        return;
    }

    auto aid=std::stoll(*said);
    auto result=m_service.GetByAnalysisID(aid);
    if(!result){
        context.setResponse(m_factory.BadRequest({std::format("violation id not found {}",aid)},request));
        return;
    }
    ns::RiskAIAnalysisEntityDto temp={std::move(*result)};
    context.setResponse(m_factory.OK(temp,request));
}
