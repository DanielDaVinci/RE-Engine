#include "RLightComponent.h"

#include "REngine/Engine/Runtime/Engine/Light/RLightSubsystem.h"

void RLightComponent::Initialize()
{
    RSceneComponent::Initialize();

    std::shared_ptr<RLightSubsystem> LightSubsystem = RLightSubsystem::Get();
    RCheckReturn(LightSubsystem);

    LightSubsystem->AddLightComponent(GetClassName(), GetSharedThis<RLightComponent>());
}
