#include "RContainerWidget.h"

#include "DebugLog/Public/Check/Check.h"
#include "GLM/gtx/string_cast.inl"

void RContainerWidget::Initialize(const std::shared_ptr<REditor>& InEditor)
{
    RWidget::Initialize(InEditor);
    
    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->Initialize(InEditor);
    }
}

void RContainerWidget::Draw()
{
    DrawChildren();
}

void RContainerWidget::Tick(float DeltaTime)
{
    RWidget::Tick(DeltaTime);

    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->Tick(DeltaTime);
    }
}

void RContainerWidget::OnKeyDown(int Key, int Scancode, int Mode)
{
    RWidget::OnKeyDown(Key, Scancode, Mode);

    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->OnKeyDown(Key, Scancode, Mode);
    }
}

void RContainerWidget::OnKeyUp(int Key, int Scancode, int Mode)
{
    RWidget::OnKeyUp(Key, Scancode, Mode);

    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->OnKeyUp(Key, Scancode, Mode);
    }
}

void RContainerWidget::OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition)
{
    RWidget::OnMouseDown(Button, Mods, CursorPosition);

    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->OnMouseDown(Button, Mods, CursorPosition);
    }
}

void RContainerWidget::OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition)
{
    RWidget::OnMouseUp(Button, Mods, CursorPosition);

    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->OnMouseUp(Button, Mods, CursorPosition);
    }
}

void RContainerWidget::OnMouseMove(const FVector2D& CursorPosition)
{
    RWidget::OnMouseMove(CursorPosition);

    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->OnMouseMove(CursorPosition);
    }
}

void RContainerWidget::AddChild(const std::shared_ptr<RWidget>& InChild)
{
    RCheckReturn(InChild);
    InChild->SetEditor(GetEditor());
    ChildrenWidgets.push_back(InChild);
}

void RContainerWidget::DrawChildren()
{
    for (const std::shared_ptr<RWidget>& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->Draw();
    }
}
