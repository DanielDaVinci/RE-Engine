#include "DebugLog/Public/Check/Check.h"
#include "Engine/REngine.h"

#pragma comment(linker, "/ignore:4099")

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    Engine = new REngine();
    RCheck(Engine);
    
    Engine->PreInit();
    Engine->Init();
    Engine->PostInit();

    while (Engine->IsEngineActive())
    {
        Engine->PreTick();
        Engine->Tick();
        Engine->PostTick();
    }

    return 0;
}