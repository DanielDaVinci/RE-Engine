#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Components/SceneComponent/RSceneComponent.h"
#include "Generated/RStaticMeshComponent.generated.h"

class FBox;
class RMesh;

class CLASS() RStaticMeshComponent : public RSceneComponent
{
    GENERATED_BODY()
    
public:
    void Initialize() override;
    void PreRender(float DeltaTime) override;
    void Render(float DeltaTime) override;

    FBox GetWorldBoundingBox() const;
    FBox GetLocalBoundingBox() const;

    void SetMesh(const std::shared_ptr<RMesh>& Mesh);

protected:
    std::shared_ptr<RMesh> StaticMesh;
    
};

META_REFLECT()

