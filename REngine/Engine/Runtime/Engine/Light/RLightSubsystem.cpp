#include "RLightSubsystem.h"

std::shared_ptr<RLightSubsystem> RLightSubsystem::Get()
{
    return GetSubsystem<RLightSubsystem>();
}

void RLightSubsystem::AddLightComponent(
    const std::string& LightClassName,
    const std::shared_ptr<RLightComponent>& LightComponent)
{
    if (!LightsMap.contains(LightClassName))
    {
        LightsMap[LightClassName] = std::vector<std::shared_ptr<RLightComponent>>();
    }

    LightsMap[LightClassName].push_back(LightComponent);
}
