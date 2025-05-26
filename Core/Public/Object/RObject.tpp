#pragma once
#include "DebugLog/Public/Check/Check.h"

template<std::derived_from<RObject> T>
std::shared_ptr<T> RObject::GetSharedThis()
{
    return std::static_pointer_cast<T>(shared_from_this());
}

template<std::derived_from<RObject> T>
std::shared_ptr<T> RObject::GetOwner() const
{
    if (auto SharedOwner = Owner.lock())
    {
        return std::static_pointer_cast<T>(SharedOwner);
    }
    
    return nullptr;
}

template <std::derived_from<RObject> T>
std::shared_ptr<T> RObject::NewObject()
{
    return NewObject<T>(GetSharedThis());
}

template <std::derived_from<RObject> T>
std::shared_ptr<T> RObject::NewObject(const std::shared_ptr<RObject>& Owner)
{
    std::shared_ptr<RObject> Object = std::make_shared<T>(Owner);
    RCheckReturn(Object, nullptr);
    Object->Construct();
    
    return std::static_pointer_cast<T>(Object);
}
