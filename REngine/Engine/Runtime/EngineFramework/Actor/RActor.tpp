#pragma once
#include "DebugLog/Public/Check/Check.h"

template <typename T, typename>
std::shared_ptr<T> RActor::AddComponent()
{
    auto Component = std::make_shared<T>(GetSharedThis());
    RCheckReturn(Component, nullptr);
    Components.push_back(Component);
    
    return Component;
}
