#include "DebugLog/Public/Check/Check.h"
#include "Engine/REngine.h"

#pragma comment(linker, "/ignore:4099")

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    Engine = std::make_shared<REngine>(nullptr);
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