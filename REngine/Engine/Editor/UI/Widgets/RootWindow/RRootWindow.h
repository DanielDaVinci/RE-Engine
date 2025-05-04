#pragma once

#include "REngine/Engine/Editor/UI/Widgets/Window/RWindow.h"

class RViewportWindow;

class RRootWindow : public RWindow
{
public:
    explicit RRootWindow(const std::shared_ptr<RObject>& InOwner);
    ~RRootWindow() override;

    void Initialize(const std::shared_ptr<REditor>& InEditor) override;
    void Draw() override;

protected:
    std::shared_ptr<RViewportWindow> ViewportWindow;
};
