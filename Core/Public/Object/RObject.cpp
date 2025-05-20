#include "RObject.h"

RObject::RObject(const std::shared_ptr<RObject>& InOwner)
{
    SetOwner(InOwner);
}

RObject::~RObject()
{
    OnDestroyed.Broadcast();
}

void RObject::Construct()
{
}

void RObject::SetOwner(const std::shared_ptr<RObject>& InOwner)
{
    Owner = InOwner;
}
