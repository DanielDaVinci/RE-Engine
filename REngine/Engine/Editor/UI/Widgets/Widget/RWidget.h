#pragma once
#include "Core/Public/Object/RObject.h"

class RWidget : public RObject
{
public:
    RWidget();
    ~RWidget() override;

    virtual void Draw() = 0;
    
};
