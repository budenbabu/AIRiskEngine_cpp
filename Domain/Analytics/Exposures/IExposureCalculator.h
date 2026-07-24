#pragma once

#include "../../../Models/Position.h"
#include "ExposureSummary.h"

class IExposureCalculator{
public:
    virtual ~IExposureCalculator()=default;
    virtual ns::ExposureSummary Calculate(const std::vector<ns::Position>& positins)const=0;
};