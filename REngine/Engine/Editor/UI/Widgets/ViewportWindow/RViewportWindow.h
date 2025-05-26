#pragma once

#include "REngine/Engine/Editor/UI/Widgets/Window/RWindow.h"

class RViewportWindow : public RWindow
{
public:
    explicit RViewportWindow(const std::shared_ptr<RObject>& InOwner);
    ~RViewportWindow() override;

    bool IsNeedDockspace() const override;
    
    void Draw() override;
    void Tick(float DeltaTime) override;
    void DrawWindowContent() const override;

    void OnKeyDown(int Key, int Scancode, int Mode) override;
    void OnKeyUp(int Key, int Scancode, int Mode) override;

    void OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition) override;
    void OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition) override;
    void OnMouseMove(const FVector2D& CursorPosition) override;

protected:
    void PushWindowStyle() override;
    void PopWindowStyle() override;

private:
    bool InputKeys[1024] = {};
    bool bIsControlling = false;
    FVector2D CursorLastPosition;
    
};
