#pragma once
#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"

template <typename T, typename>
std::shared_ptr<T> RWorld::SpawnActor(const FTransform& InTransform)
{
    std::shared_ptr<RActor> Actor = std::make_shared<T>(GetSharedThis());
    RCheckReturn(Actor, nullptr);

    Actor->SetWorld(GetSharedThis<RWorld>());
    Actor->Initialize();
    
    Actor->SetTransform(InTransform);
    
    return Actor;
}
