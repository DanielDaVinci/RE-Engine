#pragma once
#include <vector>

#include "Core/Public/Object/RObject.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"

class RMeshActor;
class RActor;

class RWorld : public RObject
{
public:
    using RObject::RObject;

    template<typename T, typename  = std::is_base_of<RActor, T>>
    std::shared_ptr<T> SpawnActor(const FTransform& InTransform);

    const std::vector<std::shared_ptr<RActor>>& GetActors() const;

    void Initialize();
    void Tick(float DeltaTime);
    void PreRender(float DeltaTime);
    void Render(float DeltaTime);

protected:
    std::vector<std::shared_ptr<RActor>> Actors;

    void RemoveActor(const std::shared_ptr<RActor>& Actor);
    void AddActor(const std::shared_ptr<RActor>& Actor);
    
    std::shared_ptr<RMeshActor> SpawnMeshActor(const FTransform& InTransform, const std::string& InMeshPath);
    
};

#include "World.tpp"
