#pragma once
#include <vector>

#include "REngine/Engine/Runtime/EngineFramework/Components/ActorComponent/RActorComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"
#include "Generated/RSceneComponent.generated.h"

class CLASS() RSceneComponent : public RActorComponent
{
    GENERATED_BODY()
    
public:
    void Construct() override;

    void AttachToComponent(const std::shared_ptr<RSceneComponent>& Component);
    void DetachFromParent();
    
    void SetTransform(const FTransform& InTransform);
    void SetPosition(const FVector& InPosition);
    void SetRotation(const FQuat& InQuaternion);
    void SetScale(const FVector& InScale);

    FTransform GetWorldTransform() const;
    FTransform GetRelativeTransform() const;

    FVector GetWorldPosition() const;
    FVector GetRelativePosition() const;
    FQuat GetRelativeRotation() const;

    FMatrix GetWorldTransformMatrix() const;
    FMatrix GetRelativeTransformMatrix() const;

    FVector GetForwardVector() const;
    FVector GetUpVector() const;
    FVector GetRightVector() const;
    
protected:
    PROPERTY()
    FTransform Transform;

    void SetParentComponent(const std::shared_ptr<RSceneComponent>& Component);
    std::shared_ptr<RSceneComponent> GetParentComponent() const;
    
    void AddComponent(const std::shared_ptr<RSceneComponent>& Component);
    void RemoveComponent(const std::shared_ptr<RSceneComponent>& Component);
    
private:
    std::weak_ptr<RSceneComponent> ParentComponent;
    std::vector<std::shared_ptr<RSceneComponent>> ChildrenComponents;

};

META_REFLECT()
