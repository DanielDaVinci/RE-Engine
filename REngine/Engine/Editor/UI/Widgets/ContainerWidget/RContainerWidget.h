#pragma once

#include <vector>
#include <memory>
#include "REngine/Engine/Editor/UI/Widgets/Widget/RWidget.h"

class RContainerWidget : public RWidget
{
public:
    explicit RContainerWidget(const std::shared_ptr<RObject>& InOwner);
    ~RContainerWidget() override;

    void Initialize(const std::shared_ptr<REditor>& InEditor) override;
    void Draw() override;
    void Tick(float DeltaTime) override;

    void OnKeyDown(int Key, int Scancode, int Mode) override;
    void OnKeyUp(int Key, int Scancode, int Mode) override;

    void OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition) override;
    void OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition) override;
    void OnMouseMove(const FVector2D& CursorPosition) override;

protected:
    virtual void AddChild(const std::shared_ptr<RWidget>& InChild);
    virtual void DrawChildren();

private:
    std::vector<std::shared_ptr<RWidget>> ChildrenWidgets;
    
};
