#include "RActorPicker.h"

#include "REngine/Engine/Editor/REditor.h"
#include "REngine/Engine/Editor/Display/Frame/RFrame.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/CameraComponent/RCameraComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/FMath.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Box/FBox.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FIntVector.h"
#include "REngine/Engine/Runtime/EngineFramework/Scene/RScene.h"
#include "REngine/Engine/Runtime/EngineFramework/Scene/World/RWorld.h"

std::shared_ptr<RActorPicker> RActorPicker::GetActorPicker()
{
    auto Scene = RScene::GetEditorScene();
    RCheckReturn(Scene, {});

    return Scene->GetActorPicker();
}

void RActorPicker::SelectActor(const std::shared_ptr<RActor>& PickedActor)
{
    if (auto SelectedActor = WeakSelectedActor.lock())
    {
        SelectedActor->SetAsSelected(false);
    }
    
    WeakSelectedActor = PickedActor;

    if (auto SelectedActor = WeakSelectedActor.lock())
    {
        SelectedActor->SetAsSelected(true);
    }
}

void RActorPicker::SelectActorAtCursor(const FVector2D& CursorPosition)
{
    SelectActor(GetActorAtCursor(CursorPosition));
}

std::shared_ptr<RActor> RActorPicker::GetActorAtCursor(const FVector2D& CursorPosition) const
{
    auto Frame = GetFrame();
    RCheckReturn(Frame, {});

    const float Depth = Frame->GetDepthAt(CursorPosition);
    if (FMath::IsNearlyEqual(Depth, 1.0f))
    {
        return nullptr;
    }

    auto World = GetWorld();
    RCheckReturn(World, nullptr);
    
    FVector WorldCursorPoint = TransformCursorToWorldPoint(CursorPosition);

    const auto& Actors = World->GetActors();
    for (const auto& Actor : Actors)
    {
        RCheckContinue(Actor);

        const FBox& BoundingBox = Actor->GetBoundingBox();
        if (BoundingBox.IsInside(WorldCursorPoint))
        {
            return Actor;
        }
    }

    return nullptr;
}

FVector RActorPicker::TransformCursorToWorldPoint(const FVector2D& CursorPosition)
{
    auto Frame = GetFrame();
    std::shared_ptr<REditor> Editor = REditor::GetEngineEditor();
    std::shared_ptr<RCameraComponent> Camera = Editor->GetCamera();
    RCheckReturn(Frame, {});
    RCheckReturn(Editor, {});
    RCheckReturn(Camera, {});

    const float Depth = Frame->GetDepthAt(CursorPosition);
    const FIntVector FrameSize = Frame->GetFrameSize();
    const FMatrix ViewMatrix = Camera->GetViewMatrix();
    const FMatrix ProjectionMatrix = Camera->GetProjectionMatrix();

    const glm::vec4 ClipSpacePoint = {
        2.0f * CursorPosition.x / FrameSize.x - 1.0f,
        2.0f * CursorPosition.y / FrameSize.y - 1.0f,
        2.0f * Depth - 1.0f,
        1.0f
    };
    
    glm::vec4 ViewSpacePoint = ProjectionMatrix.GetInverse() * ClipSpacePoint;
    ViewSpacePoint /= ViewSpacePoint.w;

    auto WorldSpawnPoint = ViewMatrix.GetInverse() * ViewSpacePoint;
    WorldSpawnPoint /= WorldSpawnPoint.w;
    
    return WorldSpawnPoint;
}

void RActorPicker::SetScene(const std::shared_ptr<RScene>& InScene)
{
    RCheckReturn(InScene);
    WeakScene = InScene;
}

std::shared_ptr<RScene> RActorPicker::GetScene() const
{
    return WeakScene.lock();
}

std::shared_ptr<RWorld> RActorPicker::GetWorld() const
{
    auto Scene = GetScene();
    RCheckReturn(Scene, {});

    return Scene->GetWorld();
}

std::shared_ptr<RFrame> RActorPicker::GetFrame()
{
    auto Editor = REditor::GetEngineEditor();
    RCheckReturn(Editor, {});

    return Editor->GetFrame();
}
