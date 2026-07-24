#pragma once
#include "PositionPnL.h"
#include "../../Models/Position.h"

class IPnLCalculator{
public:
    virtual ~IPnLCalculator()=default;
    virtual ns::PositionPnL Calculate(const ns::Position&)const=0;
};
