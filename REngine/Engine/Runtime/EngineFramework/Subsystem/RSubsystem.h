#pragma once

#include "Core/Public/Object/RObject.h"

class RSubsystem : public RObject
{
public:
    using RObject::RObject;

    template<std::derived_from<RSubsystem> T = RSubsystem>
    static std::shared_ptr<T> GetSubsystem();
    
};

#include "RSubsystem.tpp"
