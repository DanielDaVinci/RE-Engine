#include "RWidget.h"
#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Runtime/Engine/EngineWindow/REngineWindow.h"

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

void RWidget::Tick(float DeltaTime)
{
}

void RWidget::OnKeyDown(int Key, int Scancode, int Mode)
{
}

void RWidget::OnKeyUp(int Key, int Scancode, int Mode)
{
}

void RWidget::OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition)
{
    
}

void RWidget::OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition)
{
    
}

void RWidget::OnMouseMove(const FVector2D& CursorPosition)
{
    
}

void RWidget::EnableCursor()
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine);

    auto EngineWindow = Engine->GetEngineWindow();
    RCheckReturn(EngineWindow);

    EngineWindow->EnableCursor();
}

void RWidget::DisableCursor()
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine);

    auto EngineWindow = Engine->GetEngineWindow();
    RCheckReturn(EngineWindow);

    EngineWindow->DisableCursor();
}
