#include "RScene.h"

#include "World/RWorld.h"

void RScene::Initialize()
{
    World = NewObject<RWorld>();
    RCheckReturn(World);
    World->Initialize();
}

void RScene::Tick(float DeltaTime)
{
    if (RCheck(World))
    {
        World->Tick(DeltaTime);
    }
}

void RScene::Render(float DeltaTime)
{
    if (RCheck(World))
    {
        World->Render(DeltaTime);
    }
}
