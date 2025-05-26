#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"

class RCameraComponent : public RSceneComponent
{
public:
    using RSceneComponent::RSceneComponent;

    void Construct() override;

    FMatrix GetViewMatrix() const;
    FMatrix GetProjectionMatrix() const;

    void SetFOV(float InFOV);
    float GetFOV() const;

protected:
    float FOV = 90.0f;
    
};
