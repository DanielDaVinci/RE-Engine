#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"
#include "Generated/RLightComponent.generated.h"

class FShader;

class CLASS() RLightComponent : public RSceneComponent
{
    GENERATED_BODY()
    
protected:
    void Initialize() override;

    virtual void ApplyLightData(const std::shared_ptr<FShader>& Shader, int Index) = 0;
    
};

META_REFLECT()