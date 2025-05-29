#include "RStaticMeshComponent.h"

#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMesh.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMeshSubsystem.h"

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
    
    if (RCheck(StaticMesh))
    {
        StaticMesh->Render(GetWorldTransform(), DeltaTime);
    }
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
