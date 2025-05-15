#include "DebugLog/Public/Check/Check.h"
#include "Engine/REngine.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

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