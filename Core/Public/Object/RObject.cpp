#include "RObject.h"

RObject::RObject(const std::shared_ptr<RObject>& InOwner)
{
    SetOwner(InOwner);
}

RObject::~RObject()
{
}

std::shared_ptr<RObject> RObject::GetOwner() const
{
    return Owner.lock();
}

void RObject::SetOwner(const std::shared_ptr<RObject>& InOwner)
{
    Owner = InOwner;
}
