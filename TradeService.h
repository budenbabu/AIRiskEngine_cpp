#pragma once
#include <iostream>
#include <memory>
#include <functional>

class Trade
{
    static int nextId;
    int id_;

public:

    Trade(): id_(++nextId)
    {
        std::cout << "Trade "<< id_<< " Created\n";
    }

    void Execute()
    {
        std::cout << "Executing Trade "<< id_<< '\n';
    }
};

int Trade::nextId = 0;

using TradeFactory=std::function<std::unique_ptr<Trade>()>;

class TradeService{ 
    TradeFactory m_factory;
public:
    TradeService(TradeFactory factory):m_factory(factory){}
    void Process(){
        auto trade=m_factory();
        trade->Execute();
    }
};