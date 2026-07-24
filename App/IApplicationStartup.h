#pragma once

class IApplicationStartup{
public:
    virtual ~IApplicationStartup()=default;
    virtual void Run()=0;
    virtual void stop()=0;
};
