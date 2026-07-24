#include "PositionValidator.h"

ValidationResult PositionValidator::Validate(const ns::Position& position) const
{
    ValidationResult result;
    if(position.symbol.empty()) result.AddError("Symbol is required");
    if(position.quantity <=0) result.AddError("Quantity must be greater than zero");
    if(position.averagePrice <=0) result.AddError("Averge price must be greater then zero");
    return result;    
}
