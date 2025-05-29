#pragma once

#include "REngine/Engine/Editor/UI/Widgets/Window/RWindow.h"

class RFrame;

class RViewportWindow : public RWindow
{
public:
    using RWindow::RWindow;

    bool IsNeedDockspace() const override;

    void Construct() override;
    void Draw() override;
    void Tick(float DeltaTime) override;
    void DrawWindowContent() const override;

    void OnKeyDown(int Key, int Scancode, int Mode) override;
    void OnKeyUp(int Key, int Scancode, int Mode) override;

    void OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition) override;
    void OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition) override;
    void OnMouseMove(const FVector2D& CursorPosition) override;

    std::shared_ptr<RFrame> GetFrame() const;

protected:
    void PushWindowStyle() override;
    void PopWindowStyle() override;

    void PickObject(const FVector2D& CursorPosition) const;

private:
    bool InputKeys[1024] = {};
    bool bIsControlling = false;
    FVector2D CursorLastPosition;
    
};
