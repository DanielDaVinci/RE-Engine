#include "RWorld.h"

void RWorld::Initialize()
{
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
