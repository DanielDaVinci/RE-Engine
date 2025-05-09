#pragma once
#include <vector>

#include "REngine/Engine/Runtime/EngineFramework/Components/ActorComponent/RActorComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"

class RSceneComponent : public RActorComponent
{
public:
    using RActorComponent::RActorComponent;

    void AttachToComponent(const std::shared_ptr<RSceneComponent>& Component);
    void DetachFromParent();
    
    void SetTransform(const FTransform& InTransform);
    void SetPosition(const FVector& InPosition);
    void SetRotation(const FRotator& InRotation);
    void SetScale(const FVector& InScale);

    FTransform GetWorldTransform() const;
    FTransform GetRelativeTransform() const;
    
protected:
    FTransform Transform;

    void SetParentComponent(const std::shared_ptr<RSceneComponent>& Component);
    std::shared_ptr<RSceneComponent> GetParentComponent() const;
    
    void AddComponent(const std::shared_ptr<RSceneComponent>& Component);
    void RemoveComponent(const std::shared_ptr<RSceneComponent>& Component);
    
private:
    std::weak_ptr<RSceneComponent> ParentComponent;
    std::vector<std::shared_ptr<RSceneComponent>> ChildrenComponents;
    
};
