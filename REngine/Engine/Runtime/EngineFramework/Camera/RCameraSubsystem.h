#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Subsystem/RSubsystem.h"

class RCameraComponent;

class RCameraSubsystem : public RSubsystem
{
public:
    using RSubsystem::RSubsystem;

    static std::shared_ptr<RCameraSubsystem> Get();
    
    void AddCamera(const std::shared_ptr<RCameraComponent>& InCamera);
    std::shared_ptr<RCameraComponent> GetSelectedCamera() const;
    void SelectCamera(size_t CameraIndex);
    
protected:
    std::vector<std::shared_ptr<RCameraComponent>> Cameras;
    size_t SelectedCameraIndex = 0;
    
};
