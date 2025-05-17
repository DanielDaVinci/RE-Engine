#include "RContainerWidget.h"

#include "DebugLog/Public/Check/Check.h"
#include "GLM/gtx/string_cast.inl"

RContainerWidget::RContainerWidget(const std::shared_ptr<RObject>& InOwner) : RWidget(InOwner)
{
    
}

RContainerWidget::~RContainerWidget()
{
}

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
        Child->OnMouseDown(Button, Mods, CursorPosition);
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
