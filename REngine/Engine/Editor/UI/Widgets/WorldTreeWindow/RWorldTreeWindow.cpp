#include "RWorldTreeWindow.h"

#include <format>

#include "REngine/Engine/Editor/REditor.h"
#include "REngine/Engine/Runtime/EngineFramework/Scene/RScene.h"
#include "REngine/Engine/Runtime/EngineFramework/Scene/ActorPicker/RActorPicker.h"
#include "REngine/Engine/Runtime/EngineFramework/Scene/World/RWorld.h"

void RWorldTreeWindow::Construct()
{
    RWindow::Construct();
    SetWindowName("WorldTreeWindow");
}

void RWorldTreeWindow::DrawWindowContent() const
{
    RWindow::DrawWindowContent();
    
    auto Scene = RScene::GetEditorScene();
    RCheckReturn(Scene);

    auto World = Scene->GetWorld();
    RCheckReturn(World);

    auto ActorPicker = RActorPicker::GetActorPicker();
    RCheckReturn(ActorPicker);

    const auto& Actors =  World->GetActors();
    for (auto It = Actors.begin(); It != Actors.end(); ++It)
    {
        const auto& Actor = *It;
        RCheckContinue(Actor);

        const int Index = std::distance(Actors.begin(), It);

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
        if (Actor->IsSelected())
        {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        std::string NodeName = std::format("%d. {}", Actor->GetClassName());
        if (ImGui::TreeNodeEx((void*)(intptr_t)Index, flags, NodeName.c_str(), Index + 1))
        {
            if (ImGui::IsItemClicked())
            {
                ActorPicker->SelectActor(Actor);
            }
            
            ImGui::TreePop();
        }
    }
}
