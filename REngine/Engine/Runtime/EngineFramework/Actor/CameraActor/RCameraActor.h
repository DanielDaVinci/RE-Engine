#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"

class RCameraComponent;

class RCameraActor : public RActor
{
public:
    using RActor::RActor;

protected:
    std::shared_ptr<RCameraComponent> CameraComponent;
    
    void Construct() override;
};
