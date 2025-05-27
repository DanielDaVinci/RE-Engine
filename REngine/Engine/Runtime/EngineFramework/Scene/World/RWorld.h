#pragma once
#include <vector>

#include "Core/Public/Object/RObject.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"

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
    void Render(float DeltaTime);

protected:
    std::vector<std::shared_ptr<RActor>> Actors;
    
};

#include "World.tpp"
