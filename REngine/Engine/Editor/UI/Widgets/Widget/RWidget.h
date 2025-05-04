#pragma once
#include "Core/Public/Object/RObject.h"

class REditor;

class RWidget : public RObject
{
public:
    explicit RWidget(const std::shared_ptr<RObject>& InOwner);
    ~RWidget() override;

    void SetEditor(const std::shared_ptr<REditor>& InEditor);
    std::shared_ptr<REditor> GetEditor() const;

    virtual void Init(const std::shared_ptr<REditor>& InEditor);
    virtual void Draw() = 0;

protected:
    std::weak_ptr<REditor> WeakEditor;
    
};
