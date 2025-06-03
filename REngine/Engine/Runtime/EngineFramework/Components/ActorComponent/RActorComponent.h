#pragma once
#include "Core/Public/Object/RObject.h"
#include "Generated/RActorComponent.generated.h"

class CLASS() RActorComponent : public RObject
{
    GENERATED_BODY()
    
public:
    virtual void Initialize();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
    virtual void PreRender(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual void EndPlay();
};

META_REFLECT()
