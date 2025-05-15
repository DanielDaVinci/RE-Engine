#include "RMeshActor.h"

#include "REngine/Engine/Runtime/EngineFramework/Components/StaticMeshComponent/RStaticMeshComponent.h"

RMeshActor::RMeshActor(const std::shared_ptr<RObject>& InOwner) : RActor(InOwner)
{
}

void RMeshActor::Construct()
{
    RActor::Construct();

    StaticMeshComponent = AddComponent<RStaticMeshComponent>();
    RCheckReturn(StaticMeshComponent);
    StaticMeshComponent->AttachToComponent(GetRootComponent());
}
