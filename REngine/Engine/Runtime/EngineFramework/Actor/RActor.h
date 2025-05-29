#pragma once

#include <vector>
#include "Core/Public/Object/RObject.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"

class FBox;
class RSceneComponent;
class RActorComponent;

class RActor : public RObject
{
    friend class RWorld;
    
public:
    using RObject::RObject;

    RActor(const std::shared_ptr<RObject>& InOwner);
    ~RActor() override;

    // ------- Loop --------
    void Construct() override;
    virtual void Initialize();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual void EndPlay();
    // ---------------------

    void SetTransform(const FTransform& InTransform);
    void SetRelativePosition(const FVector& InPosition);
    void SetRelativeRotation(const FQuat& InQuaternion);
    
    FTransform GetTransform() const;
    FVector GetRelativePosition() const;
    FQuat GetRelativeRotation() const;

    FVector GetForwardVector() const;
    FVector GetRightVector() const;
    FVector GetUpVector() const;

    std::shared_ptr<RWorld> GetWorld() const;
    std::shared_ptr<RSceneComponent> GetRootComponent() const;

    FBox GetBoundingBox() const;

    void SetAsSelected(float InIsSelected);
    bool IsSelected() const;
    
protected:
    std::shared_ptr<RSceneComponent> RootComponent;
    std::vector<std::shared_ptr<RActorComponent>> Components;

    void SetRootComponent(const std::shared_ptr<RSceneComponent>& Component);
    
    template<std::derived_from<RActorComponent> T = RActorComponent>
    std::shared_ptr<T> AddComponent();
    void RemoveComponent(const std::shared_ptr<RActorComponent>& Component);

    bool ContainComponent(const std::shared_ptr<RActorComponent>& Component);

private:
    std::weak_ptr<RWorld> World;
    bool bIsSelected = false;

    void SetWorld(const std::shared_ptr<RWorld>& InWorld);
    
};

#include "RActor.tpp"
