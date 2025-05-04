#pragma once

template <typename T> requires std::is_base_of_v<RObject, T>
std::shared_ptr<T> RObject::GetSharedThis()
{
    return std::static_pointer_cast<T>(shared_from_this());
}