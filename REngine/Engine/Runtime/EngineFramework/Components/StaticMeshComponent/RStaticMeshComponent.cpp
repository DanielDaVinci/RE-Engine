#include "RStaticMeshComponent.h"

#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMesh.h"

void RStaticMeshComponent::Initialize()
{
    RSceneComponent::Initialize();

    SetRotation(FRotator(90.0f, 90.0f, 360.0f));

    StaticMesh = NewObject<RMesh>();
    RCheckReturn(StaticMesh);
    StaticMesh->LoadMesh("Content/objects/backpack/backpack.obj");
}

void RStaticMeshComponent::Render(float DeltaTime)
{
    RSceneComponent::Render(DeltaTime);

    if (RCheck(StaticMesh))
    {
        StaticMesh->Render(GetWorldTransformMatrix(), DeltaTime);
    }
}
