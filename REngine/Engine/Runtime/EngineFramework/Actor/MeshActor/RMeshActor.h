#pragma once

#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"
#include "Generated/RMeshActor.generated.h"

class RStaticMeshComponent;

class CLASS() RMeshActor : public RActor
{
    GENERATED_BODY()

protected:
    std::shared_ptr<RStaticMeshComponent> StaticMeshComponent;

    void Construct() override;
    void Tick(float DeltaTime) override;
};

META_REFLECT()
