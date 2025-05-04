#pragma once

#include <memory>
#include "Core/Public/Class/RClass.h"

#pragma comment(linker, "/ignore:4251")

class DLL_API RObject : public RClass, public std::enable_shared_from_this<RObject>
{
public:
    explicit RObject(const std::shared_ptr<RObject>& InOwner);
    ~RObject() override;

    template<typename T = RObject> requires std::is_base_of_v<RObject, T>
    std::shared_ptr<T> GetSharedThis();
    
    std::shared_ptr<RObject> GetOwner() const;
    
private:
    std::weak_ptr<RObject> Owner;

    void SetOwner(const std::shared_ptr<RObject>& InOwner);
};

#include "RObject.tpp"