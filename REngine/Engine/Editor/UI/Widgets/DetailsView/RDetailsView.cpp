#include "RDetailsView.h"

#include <iostream>

#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/CameraComponent/RCameraComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/StaticMeshComponent/RStaticMeshComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Scene/ActorPicker/RActorPicker.h"

void RDetailsView::Construct()
{
    RWindow::Construct();
    SetWindowName("DetailsView");
}

void RDetailsView::DrawWindowContent() const
{
    RWindow::DrawWindowContent();

    const std::shared_ptr<RActorPicker> ActorPicker = RActorPicker::GetActorPicker();
    RCheckReturn(ActorPicker);

    const std::shared_ptr<RActor> Actor = ActorPicker->GetSelectedActor();
    if (!Actor)
    {
        return;
    }
    DrawActorProperties(Actor);
}

void RDetailsView::DrawActorProperties(const std::shared_ptr<RActor>& Actor) const
{
    RCheckReturn(Actor);

    if (ImGui::TreeNodeEx(Actor->GetClassName().c_str(), ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen))
    {
        DrawValuesFromReflection(Actor.get());

        for (const auto& Component : Actor->GetAllComponents())
        {
            RCheckContinue(Component);
            DrawComponentProperties(Component);
        }
        
        ImGui::TreePop();
    }
}

void RDetailsView::DrawComponentProperties(const std::shared_ptr<RActorComponent>& Component) const
{
    RCheckReturn(Component);

    if (ImGui::TreeNodeEx(Component->GetClassName().c_str(), ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (Component->GetClassName() == RActorComponent::GetStaticClassName())
        {
            DrawValuesFromReflection(Component.get());
        }
        else if (Component->GetClassName() == RSceneComponent::GetStaticClassName())
        {
            DrawValuesFromReflection(static_cast<RSceneComponent*>(Component.get()));
        }
        else if (Component->GetClassName() == RCameraComponent::GetStaticClassName())
        {
            DrawValuesFromReflection(static_cast<RCameraComponent*>(Component.get()));
        }
        else if (Component->GetClassName() == RStaticMeshComponent::GetStaticClassName())
        {
            DrawValuesFromReflection(static_cast<RStaticMeshComponent*>(Component.get()));
        }
        
        ImGui::TreePop();
    }
}
