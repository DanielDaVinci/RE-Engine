#pragma once
#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"

template <typename T, typename>
std::shared_ptr<T> RWorld::SpawnActor(const FTransform& InTransform)
{
    std::shared_ptr<RActor> Actor = NewObject<T>();
    RCheckReturn(Actor, nullptr);

    Actor->SetWorld(GetSharedThis<RWorld>());
    Actor->SetTransform(InTransform);
    Actors.push_back(Actor);
    
    return std::static_pointer_cast<T>(Actor);
}
