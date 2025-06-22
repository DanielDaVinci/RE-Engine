#include "RStaticMeshComponent.h"

#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMesh.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMeshSubsystem.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"

void RStaticMeshComponent::Initialize()
{
    RSceneComponent::Initialize();

    if (!StaticMesh)
    {
        auto MeshSubsystem = RMeshSubsystem::Get();
        RCheckReturn(MeshSubsystem);
        
        StaticMesh = MeshSubsystem->GetMesh("Content/objects/backpack/backpack.obj");
        RCheckReturn(StaticMesh);
    }
}

void RStaticMeshComponent::PreRender(float DeltaTime)
{
    RSceneComponent::PreRender(DeltaTime);

    // const std::shared_ptr<RActor> Owner = GetOwner<RActor>();
    // RCheckReturn(Owner);
    //
    // FTransform WorldTransform = GetWorldTransform();
    //
    // if (Owner->IsSelected())
    // {
    //     RCheckReturn(StaticMesh);
    //     StaticMesh->RenderStroke(WorldTransform, DeltaTime);
    // }
}

void RStaticMeshComponent::Render(float DeltaTime)
{
    RSceneComponent::Render(DeltaTime);

    const std::shared_ptr<RActor> Owner = GetOwner<RActor>();
    RCheckReturn(Owner);
    
    RCheck(StaticMesh);
    StaticMesh->Render(GetWorldTransform(), Owner->IsSelected(), DeltaTime);
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

void RStaticMeshComponent::SetMesh(const std::shared_ptr<RMesh>& Mesh)
{
    RCheckReturn(Mesh);
    StaticMesh = Mesh;
}
