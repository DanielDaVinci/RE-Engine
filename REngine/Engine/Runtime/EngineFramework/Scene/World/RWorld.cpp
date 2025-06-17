#include "RWorld.h"

#include <algorithm>

#include "REngine/Engine/Runtime/Engine/Mesh/RMeshSubsystem.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/CameraActor/RCameraActor.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/MeshActor/RMeshActor.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/StaticMeshComponent/RStaticMeshComponent.h"

const std::vector<std::shared_ptr<RActor>>& RWorld::GetActors() const
{
    return Actors;
}

void RWorld::Initialize()
{
    SpawnActor<RCameraActor>(FTransform(
        FVector(-100.0f, 0.0f, 10.0f),
        FQuat(0.0f, 0.0f, 0.0f)));

    SpawnMeshActor(FTransform(
        FVector(0.0f, 0.0f, 10.0f),
        FQuat(0.0f, -90.0f, 90.0f),
        FVector(2.0f, 2.0f, 2.0f)),
        "Content/objects/backpack/backpack.obj");

    SpawnMeshActor(FTransform(
        FVector(0.0f, 0.0f, 0.0f),
        FQuat(0.0f, 0.0f, 90.0f),
        FVector(0.1f, 0.1f, 0.1f)),
        "Content/objects/sponza/sponza.obj");
    
    for (const std::shared_ptr<RActor>& Actor : Actors)
    {
        RCheckContinue(Actor);
        Actor->Initialize();
    }
}

void RWorld::Tick(float DeltaTime)
{
    for (const std::shared_ptr<RActor>& Actor : Actors)
    {
        RCheckContinue(Actor);
        Actor->Tick(DeltaTime);
    }
}

void RWorld::PreRender(float DeltaTime)
{
    for (const std::shared_ptr<RActor>& Actor : Actors)
    {
        RCheckContinue(Actor);
        Actor->PreRender(DeltaTime);
    }
}

void RWorld::Render(float DeltaTime)
{
    for (const std::shared_ptr<RActor>& Actor : Actors)
    {
        RCheckContinue(Actor);
        Actor->Render(DeltaTime);
    }
}

void RWorld::RemoveActor(const std::shared_ptr<RActor>& Actor)
{
    RCheckReturn(Actor);
    Actors.erase(std::ranges::remove(Actors, Actor).begin(), Actors.end());
}

void RWorld::AddActor(const std::shared_ptr<RActor>& Actor)
{
    RCheckReturn(Actor);
    Actors.push_back(Actor);
}

std::shared_ptr<RMeshActor> RWorld::SpawnMeshActor(const FTransform& InTransform, const std::string& InMeshPath)
{
    std::shared_ptr<RMeshActor> Actor = SpawnActor<RMeshActor>(InTransform);
    RCheckReturn(Actor, nullptr);

    std::shared_ptr<RStaticMeshComponent> MeshComponent = Actor->GetComponent<RStaticMeshComponent>();
    RCheckReturn(MeshComponent, nullptr);

    std::shared_ptr<RMeshSubsystem> MeshSubsystem = RMeshSubsystem::Get();
    RCheckReturn(MeshSubsystem, nullptr);

    std::shared_ptr<RMesh> Mesh = MeshSubsystem->GetMesh(InMeshPath);
    RCheckReturn(Mesh, nullptr);

    MeshComponent->SetMesh(Mesh);

    return Actor;
}
