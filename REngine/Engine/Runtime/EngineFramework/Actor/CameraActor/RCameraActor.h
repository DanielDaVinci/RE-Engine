#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"
#include "Generated/RCameraActor.generated.h"

class RCameraComponent;

class CLASS() RCameraActor : public RActor
{
    GENERATED_BODY()
    
protected:
    std::shared_ptr<RCameraComponent> CameraComponent;
    
    void Construct() override;
};

META_REFLECT()
