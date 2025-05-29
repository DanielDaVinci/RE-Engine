#include "RStaticMeshComponent.h"

#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMesh.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMeshSubsystem.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"

void RStaticMeshComponent::Initialize()
{
    RSceneComponent::Initialize();

    auto MeshSubsystem = RMeshSubsystem::Get();
    RCheckReturn(MeshSubsystem);
    
    StaticMesh = MeshSubsystem->GetMesh("Content/objects/backpack/backpack.obj");
    RCheckReturn(StaticMesh);
}

void RStaticMeshComponent::Render(float DeltaTime)
{
    RSceneComponent::Render(DeltaTime);
    RCheck(StaticMesh);

    const std::shared_ptr<RActor> OwnerActor = GetOwner<RActor>();
    RCheckReturn(OwnerActor);

    FTransform WorldTransform = GetWorldTransform();

    if (OwnerActor->IsSelected())
    {
        StaticMesh->RenderStroke(WorldTransform, DeltaTime);
    }
    
    StaticMesh->Render(WorldTransform, DeltaTime);
}

FBox RStaticMeshComponent::GetWorldBoundingBox() const
{
    return GetWorldTransformMatrix() * GetLocalBoundingBox();
}

FBox RStaticMeshComponent::GetLocalBoundingBox() const
{
    RCheckReturn(StaticMesh, {});
    return StaticMesh->GetBoundingBox();
}
