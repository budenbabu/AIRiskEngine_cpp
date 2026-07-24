#pragma once
#include <iostream>
#include "../pipeline/RequestContext.h"

class IAIAnalysisController{
public:
    virtual ~IAIAnalysisController()=default;
    virtual void getAll(RequestContext&)=0;
    virtual void getByVid(RequestContext&)=0;
    virtual void getByAid(RequestContext&)=0;
};