#pragma once
#include <string>

struct Position
{
    std::string symbol;

    int quantity;

    double averagePrice;

    double marketPrice;

    double unrealizedPnL;

    double realizedPnL;
};