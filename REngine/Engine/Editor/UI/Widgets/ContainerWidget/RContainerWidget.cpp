#include "RContainerWidget.h"

#include "DebugLog/Public/Check/Check.h"

RContainerWidget::RContainerWidget(const std::shared_ptr<RObject>& InOwner) : RWidget(InOwner)
{
    
}

RContainerWidget::~RContainerWidget()
{
}

void RContainerWidget::Init(const std::shared_ptr<REditor>& InEditor)
{
    RWidget::Init(InEditor);
    
    for (const auto& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->Init(InEditor);
    }
}

void RContainerWidget::Draw()
{
    DrawChildren();
}

void RContainerWidget::AddChild(const std::shared_ptr<RWidget>& InChild)
{
    RCheckReturn(InChild);
    InChild->SetEditor(GetEditor());
    ChildrenWidgets.push_back(InChild);
}

void RContainerWidget::DrawChildren()
{
    for (const auto& Child : ChildrenWidgets)
    {
        RCheckContinue(Child);
        Child->Draw();
    }
}
