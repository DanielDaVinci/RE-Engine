#pragma once
#include <functional>
#include <memory>

class FDelegateHandle
{
public:
    FDelegateHandle() : Id(0) {}
    explicit FDelegateHandle(size_t InId) : Id(InId) {}

    bool IsValid() const { return Id != 0; }
    size_t GetID() const { return Id; }

private:
    size_t Id;
    
};

template<typename... TArgs>
class RMulticastDelegate
{
public:
    using FuncType = std::function<void(TArgs...)>;
    
    template<typename TClass, typename... UArgs>
    FDelegateHandle AddObject(
        std::shared_ptr<TClass> Object,
        void (TClass::*ObjectMethod)(TArgs..., UArgs...),
        UArgs&&... UserArgs)
    {
        std::weak_ptr<TClass> WeakObject = Object;

        FuncType FunctionCall = [WeakObject, ObjectMethod, ...UserArgs = std::forward<UArgs>(UserArgs)](TArgs... Args)
        {
            if (auto SharedObject = WeakObject.lock())
            {
                ((*SharedObject).*ObjectMethod)(std::forward<TArgs>(Args)..., UserArgs...);
            }
        };
        
        size_t Id = ++NextId;
        Delegates.emplace(Id, FDelegateInfo(std::move(FunctionCall), WeakObject));
        return FDelegateHandle(Id);
    }

    template<typename TClass, typename... UArgs>
    FDelegateHandle AddObject(
        std::shared_ptr<TClass> Object,
        void (TClass::*ObjectMethod)(TArgs..., UArgs...) const,
        UArgs&&... UserArgs)
    {
        std::weak_ptr<TClass> WeakObject = Object;

        FuncType FunctionCall = [WeakObject, ObjectMethod, ...UserArgs = std::forward<UArgs>(UserArgs)](TArgs... Args)
        {
            if (auto SharedObject = WeakObject.lock())
            {
                ((*SharedObject).*ObjectMethod)(std::forward<TArgs>(Args)..., UserArgs...);
            }
        };
        
        size_t Id = ++NextId;
        Delegates.emplace(Id, FDelegateInfo(std::move(FunctionCall), WeakObject));
        return FDelegateHandle(Id);
    }

    template<typename TClass, typename... UArgs>
    FDelegateHandle AddUniqueObject(
        std::shared_ptr<TClass> Object,
        void (TClass::*ObjectMethod)(TArgs..., UArgs...),
        UArgs&&... UserArgs)
    {
        FDelegateHandle Handle = FindIfBound(Object);
        if (Handle.IsValid())
        {
            return Handle;
        }

        return AddObject(Object, ObjectMethod, std::forward<UArgs>(UserArgs)...);
    }

    FDelegateHandle AddStatic(void (*Function)(TArgs...))
    {
        size_t Id = ++NextId;
        Delegates.emplace(Id, FDelegateHandle(std::move(Function)));
        return FDelegateHandle(Id);
    }

    FDelegateHandle AddLambda(FuncType&& Function)
    {
        size_t Id = ++NextId;
        Delegates.emplace(Id, FDelegateInfo(std::move(Function)));
        return FDelegateHandle(Id);
    }
    
    void Remove(const FDelegateHandle& Handle)
    {
        if (Handle.IsValid())
        {
            Delegates.erase(Handle.GetID());
        }
    }

    template<typename TClass>
    void RemoveAll(const std::shared_ptr<TClass>& Object)
    {
        for (auto It = Delegates.begin(); It != Delegates.end(); )
        {
            auto& [Id, Info] = *It;
            auto& [Function, WeakObject] = Info;

            if (!WeakObject.owner_before(Object) && !Object.owner_before(WeakObject))
            {
                It = Delegates.erase(It);
            }
            else
            {
                ++It;
            }
        }
    }
    
    void Clear()
    {
        Delegates.clear();
    }
    
    void Broadcast(TArgs&&... Args)
    {
        for (auto& It : Delegates)
        {
            auto& [Function, WeakObject] = It.second;
            
            if (Function)
            {
                Function(std::forward<TArgs>(Args)...);
            }
        }
    }

    template<typename TClass>
    FDelegateHandle FindIfBound(const std::shared_ptr<TClass>& Object)
    {
        for (const auto& [Id, Info] : Delegates)
        {
            if (!Info.WeakObject.owner_before(Object) && !Object.owner_before(Info.WeakObject))
            {
                return FDelegateHandle(Id);
            }
        }

        return FDelegateHandle();
    }

    bool IsBound()
    {
        return !Delegates.empty();
    }

    RMulticastDelegate() = default;
    RMulticastDelegate(RMulticastDelegate&) = default;
    RMulticastDelegate(RMulticastDelegate&&) = default;
    RMulticastDelegate& operator=(RMulticastDelegate&&) = default;

private:
    struct FDelegateInfo
    {
        FuncType Function;
        std::weak_ptr<void> WeakObject;

        FDelegateInfo(FuncType InFunction, std::weak_ptr<void> InWeakObject = {})
            : Function(std::move(InFunction)), WeakObject(std::move(InWeakObject))
        {
        }
        
    };
    
    std::unordered_map<size_t, FDelegateInfo> Delegates;
    size_t NextId = 0;
    
};

#define DECLARE_DELEGATE(DelegateName, ...) using DelegateName = RMulticastDelegate<__VA_ARGS__>;
