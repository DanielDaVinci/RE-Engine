#include "RWindow.h"

RWindow::RWindow(const std::shared_ptr<RObject>& InOwner) : RContainerWidget(InOwner)
{
    WindowStyleNums = 0;
}

RWindow::~RWindow()
{
    
}

void RWindow::SetForcePosition(const ImVec2& Position)
{
    ImGui::SetNextWindowPos(Position);
}

void RWindow::SetForceSize(const ImVec2& Size)
{
    ImGui::SetNextWindowSize(Size);
}

void RWindow::SetForceViewport(const ImGuiID& ViewportID)
{
    ImGui::SetNextWindowViewport(ViewportID);
}

FVector2D RWindow::GetWindowPosition() const
{
    return WindowData.Position;
}

FVector2D RWindow::GetWindowSize() const
{
    return WindowData.Size;
}

void RWindow::SetWindowFlags(const ImGuiWindowFlags& Flags)
{
    WindowData.WindowFlags |= Flags;
}

void RWindow::SetRounding(float Radius)
{
    WindowData.RoundingRadius = Radius;
}

void RWindow::SetBorderSize(float Size)
{
    WindowData.BorderSize = Size;
}

void RWindow::SetPaddingSize(const ImVec2& PaddingSize)
{
    WindowData.PaddingSize = PaddingSize;
}

bool RWindow::IsPointInside(const FVector2D& Point) const
{
    const FVector2D WindowPosition = GetWindowPosition();
    const FVector2D WindowSize = GetWindowSize();

    bool bIsInsideX = Point.x > WindowPosition.x && Point.x < WindowPosition.x + WindowSize.x;
    bool bIsIndexY = Point.y > WindowPosition.y && Point.y < WindowPosition.y + WindowSize.y;
    
    return bIsInsideX && bIsIndexY;
}

bool RWindow::IsNeedDockspace() const
{
    return true;
}

void RWindow::Initialize(const std::shared_ptr<REditor>& InEditor)
{
    RContainerWidget::Initialize(InEditor);
}

void RWindow::Draw()
{
    PushWindowStyle();
    ImGui::Begin(WindowData.Name.c_str(), nullptr, WindowData.WindowFlags);
    PopWindowStyle();
    
    if (IsNeedDockspace())
    {
        InitDockspace();
    }
    WindowData.Position = ImGui::GetWindowPos();
    WindowData.Size = ImGui::GetWindowSize();

    DrawWindowContent();
    RContainerWidget::Draw();
    
    ImGui::End();
}

void RWindow::OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition)
{
    RContainerWidget::OnMouseDown(Button, Mods, CursorPosition);
}

void RWindow::OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition)
{
    RContainerWidget::OnMouseUp(Button, Mods, CursorPosition);
}

void RWindow::SetWindowName(const std::string& Name)
{
    WindowData.Name = Name;
}

std::string RWindow::GetWindowName() const
{
    return WindowData.Name;
}

void RWindow::AddWindowStyle(ImGuiStyleVar StyleIndex, float Value)
{
    ImGui::PushStyleVar(StyleIndex, Value);
    WindowStyleNums += 1;
}

void RWindow::AddWindowStyle(ImGuiStyleVar StyleIndex, const ImVec2& Value)
{
    ImGui::PushStyleVar(StyleIndex, Value);
    WindowStyleNums += 1;
}

void RWindow::PushWindowStyle()
{
    AddWindowStyle(ImGuiStyleVar_WindowRounding, WindowData.RoundingRadius);
    AddWindowStyle(ImGuiStyleVar_WindowBorderSize, WindowData.BorderSize);
    AddWindowStyle(ImGuiStyleVar_WindowPadding, WindowData.PaddingSize);
}

void RWindow::PopWindowStyle()
{
    ImGui::PopStyleVar(WindowStyleNums);
    WindowStyleNums = 0;
}

void RWindow::InitDockspace()
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID(GetWindowName().c_str());
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), WindowData.DockspaceFlags);
    }
}

void RWindow::DrawWindowContent() const
{
    
}
