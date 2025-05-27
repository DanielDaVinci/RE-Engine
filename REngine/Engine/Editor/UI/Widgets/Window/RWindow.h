#pragma once
#include <string>

#include "Data/FWindowData.h"
#include "REngine/Engine/Editor/UI/Widgets/ContainerWidget/RContainerWidget.h"

class RWindow : public RContainerWidget
{
public:
    using RContainerWidget::RContainerWidget;

    static void SetForcePosition(const ImVec2& Position);
    static void SetForceSize(const ImVec2& Size);
    static void SetForceViewport(const ImGuiID& ViewportID);

    FVector2D GetWindowPosition() const;
    FVector2D GetWindowSize() const;

    void SetWindowFlags(const ImGuiWindowFlags& Flags);
    void SetRounding(float Radius);
    void SetBorderSize(float Size);
    void SetPaddingSize(const ImVec2& PaddingSize);

    bool IsPointInside(const FVector2D& Point) const;

    virtual bool IsNeedDockspace() const;

    void Construct() override;
    void Initialize(const std::shared_ptr<REditor>& InEditor) override;
    void Draw() override;

    void OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition) override;
    void OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition) override;
    
protected:
    void SetWindowName(const std::string& Name);
    std::string GetWindowName() const;

    void AddWindowStyle(ImGuiStyleVar StyleIndex, float Value);
    void AddWindowStyle(ImGuiStyleVar StyleIndex, const ImVec2& Value);
    virtual void PushWindowStyle();
    virtual void PopWindowStyle();
    
    virtual void InitDockspace();
    virtual void DrawWindowContent() const;
    
private:
    FWindowData WindowData;
    int WindowStyleNums;
    
};
