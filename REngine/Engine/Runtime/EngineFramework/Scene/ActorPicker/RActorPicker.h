#pragma once
#include "Core/Public/Object/RObject.h"
#include "Core/Public/Delegates/RMulticastDelegate.h"

class RWorld;
struct FVector;
class RFrame;
class RActor;
struct FVector2D;
class RScene;

template class DLL_API RMulticastDelegate<int>;

class RActorPicker : public RObject
{
    friend class RScene;
    
public:
    using RObject::RObject;

    static std::shared_ptr<RActorPicker> GetActorPicker();

    void SelectActorAtCursor(const FVector2D& CursorPosition);

    std::shared_ptr<RActor> GetActorAtCursor(const FVector2D& CursorPosition) const;
    static FVector TransformCursorToWorldPoint(const FVector2D& CursorPosition);

protected:
    void SetScene(const std::shared_ptr<RScene>& InScene);
    std::shared_ptr<RScene> GetScene() const;
    std::shared_ptr<RWorld> GetWorld() const;

    static std::shared_ptr<RFrame> GetFrame();
    
private:
    std::weak_ptr<RScene> WeakScene;
    std::weak_ptr<RActor> WeakSelectedActor;
    
};
