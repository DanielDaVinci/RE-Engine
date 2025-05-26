#pragma once

#include <memory>

#include "Core/Public/DynLib.h"

class DLL_API RClass
{
public:
    RClass();
    virtual ~RClass();
    
protected:
    virtual void FillReflection();
    
private:
    // std::vector<RField> Fields;
    // std::vector<RFunction> Functions;
};
