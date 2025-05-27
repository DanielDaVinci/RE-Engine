#pragma once
#include "REngine/Engine/Editor/UI/Widgets/Window/RWindow.h"

class RWorldTreeWindow : public RWindow
{
public:
    using RWindow::RWindow;

protected:
    void Construct() override;
    void DrawWindowContent() const override;
};
