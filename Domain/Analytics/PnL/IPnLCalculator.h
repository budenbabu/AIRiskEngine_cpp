#pragma once
#include "PnL.h"
#include "../../../Models/Position.h"

class IPnLCalculator{
public:
    virtual~ IPnLCalculator()=default;
    virtual ns::PnLSummary Calculate(const std::vector<ns::Position>& poss)const=0;
};