#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"

class FBox;
class RMesh;

class RStaticMeshComponent : public RSceneComponent
{
public:
    using RSceneComponent::RSceneComponent;
    
    void Initialize() override;
    void PreRender(float DeltaTime) override;
    void Render(float DeltaTime) override;

    FBox GetWorldBoundingBox() const;
    FBox GetLocalBoundingBox() const;

protected:
    std::shared_ptr<RMesh> StaticMesh;
    
};
