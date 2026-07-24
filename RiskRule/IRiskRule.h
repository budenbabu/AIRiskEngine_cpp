#pragma once
#include <optional>
#include "RiskResult.h"
#include "../Models/Position.h"
#include "../Domain/Trade/Trade.h"

class IRiskRule{
public:
    virtual ~IRiskRule()=default;
    virtual ns::RiskResult Validate(const ns::Trade,const std::optional<ns::Position>& postion)const =0;    
};


