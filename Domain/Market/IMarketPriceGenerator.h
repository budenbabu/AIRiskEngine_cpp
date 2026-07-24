#pragma once
#include <iostream>

class IMarketPriceGenerator{
public:
    virtual ~IMarketPriceGenerator()=default;
    virtual void Start()=0;
    virtual void End()=0;
};