#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"

class RMesh;

class RStaticMeshComponent : public RSceneComponent
{
public:
    using RSceneComponent::RSceneComponent;

    void Initialize() override;
    void Render(float DeltaTime) override;

protected:
    std::shared_ptr<RMesh> StaticMesh;
    
};
