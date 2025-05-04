#include "RViewportWindow.h"

#include "GL/glew.h"
#include "DebugLog/Public/Check/Check.h"
#include "glm/vec2.hpp"
#include "REngine/Engine/Editor/REditor.h"
#include "REngine/Engine/Editor/Display/Frame/RFrame.h"
#include "REngine/Engine/Runtime/GameFramework/Camera/RCamera.h"

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
    Frame->Resize(WindowSize.x, WindowSize.y);

    std::shared_ptr<RCamera> Camera = Editor->GetCamera();
    RCheckReturn(Camera);
    
    Camera->setScreenWidth(WindowSize.x);
    Camera->setScreenHeight(WindowSize.y);
    
    const ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddImage(
        Frame->getTextureID(),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + WindowSize.x, pos.y + WindowSize.y),
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
