#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)

#include <memory>
#include "Core/Public/Class/RClass.h"

class DLL_API RObject : public RClass, public std::enable_shared_from_this<RObject>
{
public:
    explicit RObject(const std::shared_ptr<RObject>& InOwner);
    ~RObject() override;

    template<std::derived_from<RObject> T = RObject>
    std::shared_ptr<T> GetSharedThis();

    template<std::derived_from<RObject> T = RObject>
    std::shared_ptr<T> GetOwner() const;

protected:
    virtual void Construct();

    template<std::derived_from<RObject> T = RObject>
    std::shared_ptr<T> NewObject();
    
private:
    std::weak_ptr<RObject> Owner;

    void SetOwner(const std::shared_ptr<RObject>& InOwner);
};

#include "RObject.tpp"
#pragma warning(pop)