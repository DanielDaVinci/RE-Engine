#include "RMeshActor.h"

#include "REngine/Engine/Runtime/EngineFramework/Components/StaticMeshComponent/RStaticMeshComponent.h"

void RMeshActor::Construct()
{
    RActor::Construct();

    StaticMeshComponent = AddComponent<RStaticMeshComponent>();
    RCheckReturn(StaticMeshComponent);
    StaticMeshComponent->AttachToComponent(GetRootComponent());
}
