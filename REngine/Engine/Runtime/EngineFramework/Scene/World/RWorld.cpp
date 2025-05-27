#include "RWorld.h"

#include "REngine/Engine/Runtime/EngineFramework/Actor/CameraActor/RCameraActor.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/MeshActor/RMeshActor.h"

const std::vector<std::shared_ptr<RActor>>& RWorld::GetActors() const
{
    return Actors;
}

void RWorld::Initialize()
{
    SpawnActor<RMeshActor>(FTransform(
        FVector(10.0f, 0.0f, 0.0f),
        FQuat(0.0f, -90.0f, 90.0f),
        FVector::OneVector));

    SpawnActor<RCameraActor>(FTransform(
        FVector(0.0f, 0.0f, 0.0f),
        FQuat(0.0f, 0.0f, 0.0f)));
    
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

void RWorld::Render(float DeltaTime)
{
    for (const std::shared_ptr<RActor>& Actor : Actors)
    {
        RCheckContinue(Actor);
        Actor->Render(DeltaTime);
    }
}
