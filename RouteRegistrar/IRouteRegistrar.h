#pragma once

class Router;

class IRouteRegistrar{
public:
    virtual ~IRouteRegistrar()=default;
    virtual void RegisterRouter(Router& router)=0;
};
