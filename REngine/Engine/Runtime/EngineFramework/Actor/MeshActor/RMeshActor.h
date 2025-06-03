#pragma once

#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"

class RStaticMeshComponent;

class RMeshActor : public RActor
{
public:
    using RActor::RActor;

protected:
    std::shared_ptr<RStaticMeshComponent> StaticMeshComponent;

    void Construct() override;
    void Tick(float DeltaTime) override;
};
