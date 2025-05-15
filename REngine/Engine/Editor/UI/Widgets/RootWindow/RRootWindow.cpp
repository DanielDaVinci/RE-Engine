#include "RRootWindow.h"

#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Editor/UI/Widgets/ViewportWindow/RViewportWindow.h"

RRootWindow::RRootWindow(const std::shared_ptr<RObject>& InOwner) : RWindow(InOwner)
{
}

RRootWindow::~RRootWindow()
{
}

void RRootWindow::Initialize(const std::shared_ptr<REditor>& InEditor)
{
    ViewportWindow = NewObject<RViewportWindow>();
    RCheckReturn(ViewportWindow);
    AddChild(ViewportWindow);
    
    RWindow::Initialize(InEditor);
}

void RRootWindow::Draw()
{
    const ImGuiViewport* GUIViewport = ImGui::GetMainViewport();
    
    constexpr ImGuiWindowFlags RootWindowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    
    SetWindowFlags(RootWindowFlags);
    SetForcePosition(GUIViewport->WorkPos);
    SetForceSize(GUIViewport->WorkSize);
    SetForceViewport(GUIViewport->ID);
    
    RWindow::Draw();
}
