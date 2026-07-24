#pragma once
#include "ConcentrationRisk.h"
#include "../../Analytics/Exposures/ExposureSummary.h"

class IConcentrationCalculator
{
public:    
    virtual ~IConcentrationCalculator()=default;
    virtual ns::ConcentrationSummary Calculate(const ns::ExposureSummary& summary)const=0;
};

