#include "RCameraSubsystem.h"

std::shared_ptr<RCameraSubsystem> RCameraSubsystem::Get()
{
    return GetSubsystem<RCameraSubsystem>();
}

void RCameraSubsystem::AddCamera(const std::shared_ptr<RCameraComponent>& InCamera)
{
    RCheckReturn(InCamera);
    Cameras.push_back(InCamera);
}

std::shared_ptr<RCameraComponent> RCameraSubsystem::GetSelectedCamera() const
{
    return SelectedCameraIndex < Cameras.size() ? Cameras[SelectedCameraIndex] : nullptr;
}

void RCameraSubsystem::SelectCamera(size_t CameraIndex)
{
    RCheckReturn(CameraIndex < Cameras.size());
    SelectedCameraIndex = CameraIndex;
}
