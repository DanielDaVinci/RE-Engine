#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Subsystem/RSubsystem.h"

class RLightComponent;

class RLightSubsystem : public RSubsystem
{
public:
    using RSubsystem::RSubsystem;

    static std::shared_ptr<RLightSubsystem> Get();

    void AddLightComponent(const std::string& LightClassName, const std::shared_ptr<RLightComponent>& LightComponent);

protected:
    std::unordered_map<std::string, std::vector<std::shared_ptr<RLightComponent>>> LightsMap;
    
};
