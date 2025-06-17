#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"
#include "Generated/RLightComponent.generated.h"

class CLASS() RLightComponent : public RSceneComponent
{
    GENERATED_BODY()
    
public:
    
protected:
    void Initialize() override;
    
};

META_REFLECT()