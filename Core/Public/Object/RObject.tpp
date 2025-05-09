#pragma once

template<std::derived_from<RObject> T>
std::shared_ptr<T> RObject::GetSharedThis()
{
    return std::static_pointer_cast<T>(shared_from_this());
}

template<std::derived_from<RObject> T>
std::shared_ptr<T> RObject::GetOwner() const
{
    return std::static_pointer_cast<T>(Owner);
}
