#include "RWidget.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector2D.h"

#include <iostream>

RWidget::RWidget(const std::shared_ptr<RObject>& InOwner) : RObject(InOwner)
{
    
}

RWidget::~RWidget()
{
    
}

void RWidget::SetEditor(const std::shared_ptr<REditor>& InEditor)
{
    WeakEditor = InEditor;
}

std::shared_ptr<REditor> RWidget::GetEditor() const
{
    return WeakEditor.lock();
}

void RWidget::Initialize(const std::shared_ptr<REditor>& InEditor)
{
    SetEditor(InEditor);
}

void RWidget::OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition)
{
    
}

void RWidget::OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition)
{
    
}
