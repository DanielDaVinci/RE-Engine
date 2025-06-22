#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/LightComponent/RLightComponent.h"
#include "Generated/RDirectLightComponent.generated.h"
#include "GL/glew.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector2D.h"

class CLASS() RDirectLightComponent : public RLightComponent
{
    GENERATED_BODY()
    
public:
    void ApplyLightData(const std::shared_ptr<FShader>& Shader, int Index) override;

protected:
    PROPERTY()
    FVector2D ShadowMapSize = { 1024.0f, 1024.0f };

    PROPERTY()
    float NearPlaneDistance = 1.0f;

    PROPERTY()
    float FarPlaneDistance = 100.0f;
    
    void Construct() override;

    FMatrix GetViewMatrix() const;
    FMatrix GetProjectionMatrix() const;

private:
    std::shared_ptr<FShader> ShadowShader;
    GLuint ShadowMapFBO;
    GLuint ShadowMap;
    
};

META_REFLECT()
