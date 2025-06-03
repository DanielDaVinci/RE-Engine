#include "RMeshActor.h"

#include "REngine/Engine/Runtime/EngineFramework/Components/StaticMeshComponent/RStaticMeshComponent.h"

void RMeshActor::Construct()
{
    RActor::Construct();

    StaticMeshComponent = AddComponent<RStaticMeshComponent>();
    RCheckReturn(StaticMeshComponent);
    StaticMeshComponent->AttachToComponent(GetRootComponent());
}

void RMeshActor::Tick(float DeltaTime)
{
    RActor::Tick(DeltaTime);

    auto Rotation = GetRootComponent()->GetRelativeRotation();
    // Rotation.AddPitch(DeltaTime * 10.0f);
    // Rotation.AddYaw(DeltaTime * 10.0f);
    GetRootComponent()->SetRotation(Rotation);
}
