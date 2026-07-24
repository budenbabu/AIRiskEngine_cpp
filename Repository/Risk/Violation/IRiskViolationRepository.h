#pragma once

#include<vector>
#include "../../../RiskRule/RiskResult.h"


class IRiskViolationRepository {
public:
    virtual ~IRiskViolationRepository() = default;
    virtual std::uint64_t Add(const ns::RiskViolationEntity&) = 0;
    virtual std::optional<ns::RiskViolationEntity> getById(const std::uint64_t vid) = 0;
    virtual std::vector<ns::RiskViolationEntity> GetAll()const = 0;
    virtual std::vector<ns::RiskViolationEntity> getBySymbol(const std::string& symbol)const = 0;
    virtual std::vector<ns::RiskViolationEntity> getByType(const std::string& type)const = 0;
};