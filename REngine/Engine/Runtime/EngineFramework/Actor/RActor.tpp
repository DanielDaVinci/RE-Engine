#pragma once
#include "DebugLog/Public/Check/Check.h"

template <std::derived_from<RActorComponent> T>
std::shared_ptr<T> RActor::AddComponent()
{
    auto Component = NewObject<T>();
    RCheckReturn(Component, nullptr);
    Components.push_back(Component);
    
    return Component;
}
