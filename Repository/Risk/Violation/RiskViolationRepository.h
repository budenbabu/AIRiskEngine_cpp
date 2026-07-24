#pragma once

#include "IRiskViolationRepository.h"
#include "../../../Database/PostgreSqlConnectionPool.h"
#include "../../../Loogger/ILogger.h"



class RiskViolationRepository: public IRiskViolationRepository{    
    PostgreSqlConnectionPool& m_pool;    
    ILogger& m_logger;
public: 
    RiskViolationRepository(PostgreSqlConnectionPool& pool,ILogger& logger);
    std::uint64_t Add(const ns::RiskViolationEntity& violation)override;
    std::vector<ns::RiskViolationEntity> GetAll()const override;
    std::vector<ns::RiskViolationEntity> getBySymbol(const std::string& symbol)const override;
    std::vector<ns::RiskViolationEntity> getByType(const std::string& type)const override;


    // Inherited via IRiskViolationRepository
    std::optional<ns::RiskViolationEntity> getById(const std::uint64_t vid) override;

};