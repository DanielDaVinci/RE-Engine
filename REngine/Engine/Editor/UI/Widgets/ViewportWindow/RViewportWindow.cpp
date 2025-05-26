#include "RViewportWindow.h"

#include "GL/glew.h"
#include "DebugLog/Public/Check/Check.h"
#include "glm/vec2.hpp"
#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Editor/REditor.h"
#include "REngine/Engine/Editor/Display/Frame/RFrame.h"
#include "REngine/Engine/Runtime/Engine/EngineWindow/REngineWindow.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"
#include "REngine/Engine/Runtime/EngineFramework/Camera/RCameraLegacy.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/CameraComponent/RCameraComponent.h"

RViewportWindow::RViewportWindow(const std::shared_ptr<RObject>& InOwner) : RWindow(InOwner)
{
    SetWindowName("Scene");
}

RViewportWindow::~RViewportWindow()
{
}

bool RViewportWindow::IsNeedDockspace() const
{
    return false;
}

void RViewportWindow::Draw()
{
    RWindow::Draw();
}

void RViewportWindow::Tick(float DeltaTime)
{
    RWindow::Tick(DeltaTime);

    const GLfloat CameraShift = 5.0f * DeltaTime;
    const auto CameraComponent = REditor::GetCamera();
    RCheckReturn(CameraComponent);

    const auto CameraActor = CameraComponent->GetOwner<RActor>();
    RCheckReturn(CameraActor);
    
    if (InputKeys[GLFW_KEY_W])
    {
        CameraActor->SetRelativePosition(CameraActor->GetRelativePosition() + CameraActor->GetForwardVector() * CameraShift);
    }
    if (InputKeys[GLFW_KEY_S])
    {
        CameraActor->SetRelativePosition(CameraActor->GetRelativePosition() - CameraActor->GetForwardVector() * CameraShift);
    }
    if (InputKeys[GLFW_KEY_A])
    {
        CameraActor->SetRelativePosition(CameraActor->GetRelativePosition() - CameraActor->GetRightVector() * CameraShift);
    }
    if (InputKeys[GLFW_KEY_D])
    {
        CameraActor->SetRelativePosition(CameraActor->GetRelativePosition() + CameraActor->GetRightVector() * CameraShift);
    }
}

void RViewportWindow::DrawWindowContent() const
{
    RWindow::DrawWindowContent();

    glm::ivec2 WindowSize = glm::ivec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
    glViewport(0, 0, WindowSize.x, WindowSize.y);

    std::shared_ptr<REditor> Editor = GetEditor();
    RCheckReturn(Editor);

    std::shared_ptr<RFrame> Frame = Editor->GetFrame();
    RCheckReturn(Frame);
    Frame->SetFrameSize(WindowSize.x, WindowSize.y);

    std::shared_ptr<RCameraComponent> Camera = REditor::GetCamera();
    RCheckReturn(Camera);
    
    const ImVec2 WindowPosition = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddImage(
        Frame->getTextureID(),
        ImVec2(WindowPosition.x, WindowPosition.y),
        ImVec2(WindowPosition.x + WindowSize.x, WindowPosition.y + WindowSize.y),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
}

void RViewportWindow::OnKeyDown(int Key, int Scancode, int Mode)
{
    RWindow::OnKeyDown(Key, Scancode, Mode);

    InputKeys[Key] = true;
}

void RViewportWindow::OnKeyUp(int Key, int Scancode, int Mode)
{
    RWindow::OnKeyUp(Key, Scancode, Mode);

    InputKeys[Key] = false;
}

void RViewportWindow::OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition)
{
    RWindow::OnMouseDown(Button, Mods, CursorPosition);

    if (IsPointInside(CursorPosition) && Button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        bIsControlling = true;
        CursorLastPosition = CursorPosition;
        DisableCursor();
    }
}

void RViewportWindow::OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition)
{
    RWindow::OnMouseUp(Button, Mods, CursorPosition);

    if (bIsControlling && Button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        bIsControlling = false;
        EnableCursor();
    }
}

void RViewportWindow::OnMouseMove(const FVector2D& CursorPosition)
{
    RWindow::OnMouseMove(CursorPosition);

    if (bIsControlling)
    {
        constexpr float Sensitivity = 0.05f;
        const FVector2D Delta = CursorPosition - CursorLastPosition;
        const FVector2D Shift = Delta * Sensitivity;

        const auto CameraComponent = REditor::GetCamera();
        RCheckReturn(CameraComponent);

        const auto CameraActor = CameraComponent->GetOwner<RActor>();
        RCheckReturn(CameraActor);

        FQuat CameraRotation = CameraActor->GetRelativeRotation();
        CameraRotation.AddWorldYaw(-1.0f * Shift.x);
        CameraRotation.AddPitch(Shift.y);

        CameraActor->SetRelativeRotation(CameraRotation);
        CursorLastPosition = CursorPosition;
    }
}

void RViewportWindow::PushWindowStyle()
{
    RWindow::PushWindowStyle();
}

void RViewportWindow::PopWindowStyle()
{
    RWindow::PopWindowStyle();
}
