#include "RCameraActor.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/CameraComponent/RCameraComponent.h"

void RCameraActor::Construct()
{
    RActor::Construct();

    RemoveComponent(GetRootComponent());
    SetRootComponent(AddComponent<RCameraComponent>());
}
