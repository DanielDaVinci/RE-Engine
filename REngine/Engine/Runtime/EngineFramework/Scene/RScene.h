#pragma once
#include "Core/Public/Object/RObject.h"

class RWorld;

class RScene : public RObject
{
public:
    using RObject::RObject;

    void Initialize();
    void Tick(float DeltaTime);
    void Render(float DeltaTime);
    
protected:
    

private:
    std::shared_ptr<RWorld> World;
    
};
