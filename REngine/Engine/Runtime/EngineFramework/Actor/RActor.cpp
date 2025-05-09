#include "RActor.h"

#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"

RActor::RActor(const std::shared_ptr<RObject>& InOwner) : RObject(InOwner)
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

FTransform RActor::GetTransform() const
{
    RCheckReturn(RootComponent, {});
    return RootComponent->GetRelativeTransform();
}

std::shared_ptr<RWorld> RActor::GetRWorld() const
{
    return World.lock();
}

void RActor::SetRootComponent(const std::shared_ptr<RSceneComponent>& Component)
{
    RCheckReturn(Component);
    RCheckReturn(ContainComponent(Component));

    RootComponent = Component;
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
