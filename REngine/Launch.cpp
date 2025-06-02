#include "DebugLog/Public/Check/Check.h"
#include "Engine/REngine.h"
#include "Refl/refl.hpp"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

// struct MyClass;

class ASD
{
public:
    int b;
};

REFL_AUTO(type(ASD))

class MyClass : public ASD
{
    
private:
    int a;
    
};

REFL_TYPE(MyClass, bases<ASD>)
    REFL_FIELD(a)
    
REFL_END

int main()
{
    const std::shared_ptr<REngine> Engine = REngine::GetEngine();
    RCheck(Engine);
    
    Engine->PreInitialize();
    Engine->Initialize();
    Engine->PostInitialize();

    while (Engine->IsEngineActive())
    {
        Engine->PreTick();
        Engine->Tick();
        Engine->PostTick();
    }

    return 0;
}