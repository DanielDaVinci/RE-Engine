#include "RViewportWindow.h"

#include "GL/glew.h"
#include "DebugLog/Public/Check/Check.h"
#include "glm/vec2.hpp"
#include "REngine/Engine/Editor/REditor.h"
#include "REngine/Engine/Editor/Display/Frame/RFrame.h"
#include "REngine/Engine/Runtime/EngineFramework/Camera/RCameraLegacy.h"

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

void RViewportWindow::PushWindowStyle()
{
    RWindow::PushWindowStyle();
}

void RViewportWindow::PopWindowStyle()
{
    RWindow::PopWindowStyle();
}
