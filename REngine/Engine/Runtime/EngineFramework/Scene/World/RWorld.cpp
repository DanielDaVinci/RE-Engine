#include "RWorld.h"

#include "REngine/Engine/Runtime/EngineFramework/Actor/MeshActor/RMeshActor.h"

void RWorld::Initialize()
{
    SpawnActor<RMeshActor>({});
    
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
