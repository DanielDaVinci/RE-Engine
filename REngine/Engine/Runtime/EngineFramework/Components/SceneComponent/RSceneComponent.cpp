#include "RSceneComponent.h"

#include <algorithm>

#include "DebugLog/Public/Check/Check.h"
#include "GLM/gtc/matrix_inverse.hpp"

void RSceneComponent::Construct()
{
    RActorComponent::Construct();

    SetPosition(FVector::ZeroVector);
    SetRotation(FQuat::ZeroQuat);
    SetScale(FVector::OneVector);
}

void RSceneComponent::AttachToComponent(const std::shared_ptr<RSceneComponent>& Component)
{
    RCheckReturn(Component);
    DetachFromParent();

    SetParentComponent(Component);
    Component->AddComponent(Component);
}

void RSceneComponent::DetachFromParent()
{
    const std::shared_ptr<RSceneComponent> ParentPtr = ParentComponent.lock();
    if (!ParentPtr)
    {
        return;
    }

    ParentPtr->RemoveComponent(GetSharedThis<RSceneComponent>());
    ParentComponent.reset();
}

void RSceneComponent::SetTransform(const FTransform& InTransform)
{
    Transform = InTransform;
}

void RSceneComponent::SetPosition(const FVector& InPosition)
{
    Transform.Position = InPosition;
}

void RSceneComponent::SetRotation(const FQuat& InQuaternion)
{
    Transform.Quaternion = InQuaternion;
}

void RSceneComponent::SetScale(const FVector& InScale)
{
    Transform.Scale = InScale;
}

FTransform RSceneComponent::GetWorldTransform() const
{
    return FTransform(GetWorldTransformMatrix());
}

FTransform RSceneComponent::GetRelativeTransform() const
{
    return Transform;
}

FVector RSceneComponent::GetWorldPosition() const
{
    return GetWorldTransform().Position;
}

FVector RSceneComponent::GetRelativePosition() const
{
    return Transform.Position;
}

FQuat RSceneComponent::GetRelativeRotation() const
{
    return Transform.Quaternion;
}

FMatrix RSceneComponent::GetWorldTransformMatrix() const
{
    if (const std::shared_ptr<RSceneComponent> Parent = GetParentComponent())
    {
        return Parent->GetWorldTransformMatrix() * GetRelativeTransformMatrix();
    }

    return GetRelativeTransformMatrix();
}

FMatrix RSceneComponent::GetRelativeTransformMatrix() const
{
    return Transform.GetMatrix();
}

FVector RSceneComponent::GetForwardVector() const
{
    const FTransform WorldTransform = GetWorldTransform();
    return WorldTransform.Quaternion * FVector::ForwardVector;
}

FVector RSceneComponent::GetUpVector() const
{
    const FTransform WorldTransform = GetWorldTransform();
    return WorldTransform.Quaternion * FVector::UpVector;
}

FVector RSceneComponent::GetRightVector() const
{
    const FTransform WorldTransform = GetWorldTransform();
    return WorldTransform.Quaternion * FVector::LeftVector;
}

void RSceneComponent::SetParentComponent(const std::shared_ptr<RSceneComponent>& Component)
{
    ParentComponent = Component;
}

std::shared_ptr<RSceneComponent> RSceneComponent::GetParentComponent() const
{
    return ParentComponent.lock();
}

void RSceneComponent::AddComponent(const std::shared_ptr<RSceneComponent>& Component)
{
    RCheckReturn(Component);
    RCheckReturn(std::ranges::find(ChildrenComponents, Component) == ChildrenComponents.end());

    ChildrenComponents.push_back(Component);
}

void RSceneComponent::RemoveComponent(const std::shared_ptr<RSceneComponent>& Component)
{
    RCheckReturn(Component);
    
    auto It = std::ranges::remove(ChildrenComponents, Component);
    ChildrenComponents.erase(It.begin(), It.end());
}

void RSceneComponent::Tick(float DeltaTime)
{
    RActorComponent::Tick(DeltaTime);
}
