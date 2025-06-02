#pragma once

#include <memory>

#include "Core/Public/DynLib.h"
#include "MetaReflection/MetaReflection.h"
#include "Generated/RClass.generated.h"

class DLL_API CLASS() RClass
{
    GENERATED_BODY()
    
public:
    RClass();
    virtual ~RClass();

    PROPERTY()
    int x;
    
protected:
    virtual void FillReflection();
    
};
