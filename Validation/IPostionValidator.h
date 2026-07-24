#pragma once

#include "ValidationResult.h"
#include "../Models/Position.h"

class IPositionValidator{
public:
    virtual ~IPositionValidator()=default;
    virtual ValidationResult Validate(const ns::Position& value)const =0;
};