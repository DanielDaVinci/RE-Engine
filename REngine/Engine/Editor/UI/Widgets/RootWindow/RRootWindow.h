#pragma once

#include "REngine/Engine/Editor/UI/Widgets/Window/RWindow.h"

class RWorldTreeWindow;
class RViewportWindow;

class RRootWindow : public RWindow
{
public:
    using RWindow::RWindow;

    void Initialize(const std::shared_ptr<REditor>& InEditor) override;
    void Draw() override;

protected:
    std::shared_ptr<RViewportWindow> ViewportWindow;
    std::shared_ptr<RWorldTreeWindow> WorldTreeWindow;
    
};
