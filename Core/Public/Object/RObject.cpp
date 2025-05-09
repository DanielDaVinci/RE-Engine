#include "RObject.h"

RObject::RObject(const std::shared_ptr<RObject>& InOwner)
{
    SetOwner(InOwner);
}

RObject::~RObject()
{
}

void RObject::SetOwner(const std::shared_ptr<RObject>& InOwner)
{
    Owner = InOwner;
}
