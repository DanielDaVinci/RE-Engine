#pragma once

#include "REngine/Engine/Editor/UI/Widgets/Window/RWindow.h"

class RViewportWindow : public RWindow
{
public:
    explicit RViewportWindow(const std::shared_ptr<RObject>& InOwner);
    ~RViewportWindow() override;

    bool IsNeedDockspace() const override;
    
    void Draw() override;
    void DrawWindowContent() const override;

protected:
    void PushWindowStyle() override;
    void PopWindowStyle() override;
};
