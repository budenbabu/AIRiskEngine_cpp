#pragma once
#include "../../Domain/Market/Quote.h"

struct PriceUpdatedEvent
{
    ns::Quote quote;
};
