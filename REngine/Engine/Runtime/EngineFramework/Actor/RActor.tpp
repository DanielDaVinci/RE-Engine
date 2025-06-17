#pragma once
#include "DebugLog/Public/Check/Check.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/ActorComponent/RActorComponent.h"

template <std::derived_from<RActorComponent> T>
std::shared_ptr<T> RActor::AddComponent()
{
    auto Component = NewObject<T>();
    RCheckReturn(Component, nullptr);
    Components.push_back(Component);
    
    return Component;
}

template<std::derived_from<RActorComponent> T>
std::shared_ptr<T> RActor::GetComponent()
{
    for (const std::shared_ptr<RActorComponent>& Component : Components)
    {
        if (Component->GetClassName() == T::GetStaticClassName())
        {
            return std::static_pointer_cast<T>(Component);
        }
    }

    return nullptr;
}