#include "RActor.h"

#include <algorithm>

#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"

RActor::RActor(const std::shared_ptr<RObject>& InOwner) : RObject(InOwner)
{
}

RActor::~RActor()
{
}

void RActor::Construct()
{
    SetRootComponent(AddComponent<RSceneComponent>());
}

void RActor::Initialize()
{
    for (const std::shared_ptr<RActorComponent>& Component : Components)
    {
        RCheckContinue(Component);
        Component->Initialize();
    }
}

void RActor::BeginPlay()
{
}

void RActor::Tick(float DeltaTime)
{
    for (const std::shared_ptr<RActorComponent>& Component : Components)
    {
        RCheckContinue(Component);
        Component->Tick(DeltaTime);
    }
}

void RActor::Render(float DeltaTime)
{
    for (const std::shared_ptr<RActorComponent>& Component : Components)
    {
        RCheckContinue(Component);
        Component->Render(DeltaTime);
    }
}

void RActor::EndPlay()
{
}

void RActor::SetTransform(const FTransform& InTransform)
{
    RCheckReturn(RootComponent);
    RootComponent->SetTransform(InTransform);
}

void RActor::SetRelativePosition(const FVector& InPosition)
{
    RCheckReturn(RootComponent);
    return RootComponent->SetPosition(InPosition);
}

void RActor::SetRelativeRotation(const FQuat& InQuaternion)
{
    RCheckReturn(RootComponent);
    return RootComponent->SetRotation(InQuaternion);
}

FTransform RActor::GetTransform() const
{
    RCheckReturn(RootComponent, {});
    return RootComponent->GetRelativeTransform();
}

FVector RActor::GetRelativePosition() const
{
    RCheckReturn(RootComponent, {});
    return RootComponent->GetRelativePosition();
}

FQuat RActor::GetRelativeRotation() const
{
    RCheckReturn(RootComponent, {});
    return RootComponent->GetRelativeRotation();
}

FVector RActor::GetForwardVector() const
{
    RCheckReturn(RootComponent, {});
    return RootComponent->GetForwardVector();
}

FVector RActor::GetRightVector() const
{
    RCheckReturn(RootComponent, {});
    return RootComponent->GetRightVector();
}

FVector RActor::GetUpVector() const
{
    RCheckReturn(RootComponent, {});
    return RootComponent->GetUpVector();
}

std::shared_ptr<RWorld> RActor::GetWorld() const
{
    return World.lock();
}

std::shared_ptr<RSceneComponent> RActor::GetRootComponent() const
{
    return RootComponent;
}

void RActor::SetRootComponent(const std::shared_ptr<RSceneComponent>& Component)
{
    RCheckReturn(Component);
    RCheckReturn(ContainComponent(Component));

    RootComponent = Component;
}

void RActor::RemoveComponent(const std::shared_ptr<RActorComponent>& Component)
{
    Components.erase(std::ranges::remove(Components, Component).begin(), Components.end());
}

bool RActor::ContainComponent(const std::shared_ptr<RActorComponent>& Component)
{
    return std::ranges::find(Components, Component) != Components.end();
}

void RActor::SetWorld(const std::shared_ptr<RWorld>& InWorld)
{
    RCheckReturn(InWorld);
    World = InWorld;;
}
