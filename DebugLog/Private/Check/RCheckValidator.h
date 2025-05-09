#pragma once

#include <memory>

template<typename T>
struct RCheckValidator
{
    static constexpr bool IsBoolConvertable = std::is_constructible_v<T, bool>;
    
    template<typename TInner, typename = std::enable_if_t<IsBoolConvertable>>
    static bool IsValid(const TInner& Value)
    {
        return static_cast<bool>(Value);
    }

    template<typename TInner>
    static bool IsValid(const std::weak_ptr<TInner>& Value)
    {
        return !!Value.lock();
    }

    template<typename TInner>
    static bool IsValid(const std::shared_ptr<TInner>& Value)
    {
        return !!Value;
    }

    template<typename TInner>
    static bool IsValid(const std::unique_ptr<TInner>& Value)
    {
        return !!Value;
    }
};
