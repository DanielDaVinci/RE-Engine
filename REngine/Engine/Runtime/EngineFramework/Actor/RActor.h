#pragma once

#include <vector>
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"
#include "Core/Public/Object/RObject.h"
#include "Generated/RActor.generated.h"

class FBox;
class RSceneComponent;
class RActorComponent;

class CLASS() RActor : public RObject
{
    GENERATED_BODY()
    
    friend class RWorld;
    
public:
    // ------- Loop --------
    void Construct() override;
    virtual void Initialize();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
    virtual void PreRender(float DeltaTime);
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

META_REFLECT()

#include "RActor.tpp"
