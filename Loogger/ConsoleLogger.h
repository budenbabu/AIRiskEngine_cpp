#pragma once
#include <iostream>
#include "ILogger.h"

class ConsoleLogger:public ILogger{
public:
    void Info(std::string_view msg)override{
        std::cout<<"[INFO] "<<msg<<'\n';
    }
    void Warning(std::string_view msg)override{
        std::cout<<"[WAR] "<<msg<<'\n';
    }
    void Error(std::string_view msg)override{
        std::cout<<"[ERROR] "<<msg<<'\n';
    }
};