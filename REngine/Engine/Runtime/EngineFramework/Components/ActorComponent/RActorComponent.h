#pragma once
#include "Core/Public/Object/RObject.h"

class RActorComponent : public RObject
{
public:
    using RObject::RObject;

    virtual void Initialize();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual void EndPlay();
};
