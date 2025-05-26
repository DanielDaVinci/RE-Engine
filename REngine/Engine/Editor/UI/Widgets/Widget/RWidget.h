#pragma once
#include "Core/Public/Object/RObject.h"

struct FVector2D;
class REditor;

class RWidget : public RObject
{
public:
    explicit RWidget(const std::shared_ptr<RObject>& InOwner);
    ~RWidget() override;

    void SetEditor(const std::shared_ptr<REditor>& InEditor);
    std::shared_ptr<REditor> GetEditor() const;

    virtual void Initialize(const std::shared_ptr<REditor>& InEditor);
    virtual void Draw() = 0;
    virtual void Tick(float DeltaTime);

    virtual void OnKeyDown(int Key, int Scancode, int Mode);
    virtual void OnKeyUp(int Key, int Scancode, int Mode);

    virtual void OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition);
    virtual void OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition);
    virtual void OnMouseMove(const FVector2D& CursorPosition);

protected:
    std::weak_ptr<REditor> WeakEditor;

    static void EnableCursor();
    static void DisableCursor();
};
