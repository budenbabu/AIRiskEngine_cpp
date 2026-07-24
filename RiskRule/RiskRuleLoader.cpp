#include "RiskRuleLoader.h"
#include <format>

RiskRuleLoader::RiskRuleLoader(IRiskRuleRepository& repo, RiskRuleFactory& factory, RiskEngine& engine,ILogger& logger):
	m_engine(engine),m_factory(factory),m_repo(repo),m_logger(logger)
{
	Load();
}

void RiskRuleLoader::Load()
{
	auto rules = m_repo.GetAll();
	for (const auto& entity : rules) {
		try {
			auto rule = m_factory.Create(*entity);
			if (rule) m_engine.AddRule(std::move(rule));
		}
		catch (std::exception& ex) {
			m_logger.Error(std::format("Loader exception: {}", ex.what()));
		}
	}
	m_logger.Info(std::format("Load is completed {}",m_engine.getCount()));
}

void RiskRuleLoader::ReLoad()
{
	try {
		auto reuls = m_repo.GetAll();
		m_engine.Clear();
		std::size_t count{};
		for (const auto& entity : reuls) {
			auto rule = m_factory.Create(*entity);
			if (!rule) continue;
				m_engine.AddRule(std::move(rule));
				++count;
		}
		m_logger.Info(std::format("ReLoad is completed {}",count));
	}
	catch (const std::exception& ex) {
		m_logger.Error(
			std::format(
				"RiskRuleLoader::Reload Exception: {}",
				ex.what()));
	}
	
}
