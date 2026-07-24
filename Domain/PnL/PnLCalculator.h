#pragma once
#include "IPnLCalculator.h"

class PnLCalculator: public IPnLCalculator
{
public:
    ns::PositionPnL Calculate(const ns::Position& pos)const override;
};


