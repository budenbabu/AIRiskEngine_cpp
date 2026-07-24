#pragma once
#include <string>

class ILogger{
public:
    virtual ~ILogger()=default;
    virtual void Info(std::string_view msg)=0;
    virtual void Warning(std::string_view msg)=0;
    virtual void Error(std::string_view msg)=0;
};