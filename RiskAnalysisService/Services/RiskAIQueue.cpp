#include "RiskAIQueue.h"

RiskAIQueue::RiskAIQueue(std::shared_ptr<AIExecutor> executor, IRiskAIAnalysisService& service,IAIJobRepository& repo,ILogger& logger):
	m_executor(executor),m_service(service),m_repo(repo),m_logger(logger){}

void RiskAIQueue::Enqueue(uint64_t violationId)
{
	m_executor->Post([this, violationId] {
		try {			
			auto jobid=m_repo.Create(violationId);			
			Process({.violationId=violationId,.jobid=jobid});
		}catch (const std::exception& ex) {
			m_logger.Error(std::format("AI Worker Exception {}", ex.what()));
		}
	});
}

 void RiskAIQueue::Enqueue(const AIQueueItem& item)
 {
 	m_executor->Post([this, item] {Process(item); });
 }

void RiskAIQueue::Process(const AIQueueItem& item)
{	
	 try {
	 	m_repo.updateStatus(item.jobid, ns::AIJobStatus::Processing);
	 	m_logger.Info(std::format("AU worker started {}", item.jobid));
	 	m_service.Analysis(item.violationId);
		m_logger.Info(std::format("AU worker completed {}", item.jobid));
	 	m_repo.updateStatus(item.jobid, ns::AIJobStatus::Completed);
	 }catch (const std::exception& ex) {
	 	m_logger.Error(std::format("RiskAIQueue::Process:Exception: {}", ex.what()));
	 	m_repo.MakeFailed(item.jobid, ex.what());
	 }
}

void RiskAIQueue::RecoverPendingJobs()
{
	auto pjobs=m_repo.GetPendingJobs();
	for(auto& job: pjobs)
		Enqueue({.violationId=job.violationId,.jobid=job.jobID});
}

// uint64_t RiskAIQueue::Create(uint64_t violationId)
// {
// 	auto jobid=m_repo.Create(violationId);
//     return jobid;
// }
