#pragma once

#include <vector>
#include "Core/Public/Object/RObject.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"

class RSceneComponent;
class RActorComponent;

class RActor : public RObject
{
    friend class RWorld;
    
public:
    using RObject::RObject;

    RActor(const std::shared_ptr<RObject>& InOwner);

    // ------- Loop --------
    void Construct() override;
    virtual void Initialize();
    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual void EndPlay();

    void SetTransform(const FTransform& InTransform);
    FTransform GetTransform() const;

    std::shared_ptr<RWorld> GetWorld() const;
    std::shared_ptr<RSceneComponent> GetRootComponent() const;
    
protected:
    std::shared_ptr<RSceneComponent> RootComponent;
    std::vector<std::shared_ptr<RActorComponent>> Components;

    void SetRootComponent(const std::shared_ptr<RSceneComponent>& Component);
    
    template<typename T, typename = std::is_base_of<RActorComponent, T>>
    std::shared_ptr<T> AddComponent();

    bool ContainComponent(const std::shared_ptr<RActorComponent>& Component);

private:
    std::weak_ptr<RWorld> World;

    void SetWorld(const std::shared_ptr<RWorld>& InWorld);
    
};

#include "RActor.tpp"
