#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)

#include <memory>
#include "Core/Public/Class/RClass.h"
#include "Core/Public/Delegates/RMulticastDelegate.h"
#include "Generated/RObject.generated.h"

class CLASS() RObject : public std::enable_shared_from_this<RObject>, public RClass
{
    GENERATED_BODY()
    
public:
    DECLARE_DELEGATE(FOnDestroyedSignature)
    FOnDestroyedSignature OnDestroyed;
    
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

    template<std::derived_from<RObject> T = RObject>
    static std::shared_ptr<T> NewObject(const std::shared_ptr<RObject>& Owner);
    
private:
    std::weak_ptr<RObject> Owner;

    void SetOwner(const std::shared_ptr<RObject>& InOwner);
};

META_REFLECT()

#include "RObject.tpp"
#pragma warning(pop)