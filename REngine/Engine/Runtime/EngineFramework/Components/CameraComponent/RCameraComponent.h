#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"
#include "Generated/RCameraComponent.generated.h"

class CLASS() RCameraComponent : public RSceneComponent
{
    GENERATED_BODY()
    
public:
    void Construct() override;

    FMatrix GetViewMatrix() const;
    FMatrix GetProjectionMatrix() const;

    void SetFOV(float InFOV);
    float GetFOV() const;

protected:
    PROPERTY()
    float FOV = 90.0f;

    void Tick(float DeltaTime) override;
    
};

META_REFLECT()
