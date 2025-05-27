#include "RScene.h"

#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Editor/REditor.h"
#include "World/RWorld.h"

std::shared_ptr<RScene> RScene::GetScene()
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine, {});

    auto Editor = Engine->GetEditor();
    RCheckReturn(Editor, {});

    return Editor->GetScene();
}

std::shared_ptr<RWorld> RScene::GetWorld() const
{
    return World;
}

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
