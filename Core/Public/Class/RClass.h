#pragma once

#include "Core/Public/DynLib.h"

class DLL_API RClass
{
public:
    RClass();
    virtual ~RClass() = default;

    int b;

protected:
    virtual void FillReflection();
    
private:
    // std::vector<RField> Fields;
    // std::vector<RFunction> Functions;
};
