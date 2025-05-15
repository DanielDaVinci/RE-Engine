#pragma once

#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"

class RStaticMeshComponent;

class RMeshActor : public RActor
{
public:
    using RActor::RActor;

    RMeshActor(const std::shared_ptr<RObject>& InOwner);
    void Construct() override;

protected:
    std::shared_ptr<RStaticMeshComponent> StaticMeshComponent;
};
