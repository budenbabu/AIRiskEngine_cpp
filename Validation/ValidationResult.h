#pragma once

#include <string>
#include <vector>

class ValidationResult{
    std::vector<std::string> m_errors;
public:
    void AddError(std::string error){ m_errors.push_back(std::move(error)); }
    bool IsValid()const{ return m_errors.empty(); }
    const std::vector<std::string>& Errors()const{ return m_errors; }
};