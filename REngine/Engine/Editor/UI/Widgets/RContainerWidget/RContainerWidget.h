#pragma once

#include <vector>
#include <memory>

#include "REngine/Engine/Editor/UI/Widgets/Widget/RWidget.h"

class RContainerWidget : public RWidget
{
public:
    RContainerWidget();
    ~RContainerWidget();

    void Draw() override;

protected:
    virtual void DrawChild();

private:
    std::vector<std::shared_ptr<RWidget>> ChildrenWidgets;
    
};
