#pragma once

#include "IPostionValidator.h"

class PositionValidator:public IPositionValidator{
public:
    ValidationResult Validate(const ns::Position& position)const override;
};