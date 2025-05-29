#include "RScene.h"

#include "ActorPicker/RActorPicker.h"
#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Editor/REditor.h"
#include "World/RWorld.h"

std::shared_ptr<RScene> RScene::GetEditorScene()
{
    auto Editor = REditor::GetEngineEditor();
    RCheckReturn(Editor, {});

    return Editor->GetScene();
}

std::shared_ptr<RActorPicker> RScene::GetActorPicker() const
{
    return ActorPicker;
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
    
    ActorPicker = NewObject<RActorPicker>();
    RCheckReturn(ActorPicker);
    ActorPicker->SetScene(GetSharedThis<RScene>());
    
}

void RScene::Tick(float DeltaTime)
{
    if (RCheck(World))
    {
        World->Tick(DeltaTime);
    }
}

void RScene::PreRender(float DeltaTime)
{
    if (RCheck(World))
    {
        World->PreRender(DeltaTime);
    }
}

void RScene::Render(float DeltaTime)
{
    if (RCheck(World))
    {
        World->Render(DeltaTime);
    }
}
