#include "RCameraComponent.h"

#include "REngine/Engine/Editor/Display/Frame/RFrame.h"
#include "REngine/Engine/Runtime/EngineFramework/Camera/RCameraSubsystem.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/FMath.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FIntVector.h"

void RCameraComponent::Construct()
{
    RSceneComponent::Construct();

    const std::shared_ptr<RCameraSubsystem> CameraSubsystem = RCameraSubsystem::Get();
    RCheckReturn(CameraSubsystem);

    CameraSubsystem->AddCamera(GetSharedThis<RCameraComponent>());
}

FMatrix RCameraComponent::GetViewMatrix() const
{
    const FVector WorldPosition = GetWorldPosition();
    return glm::lookAt(WorldPosition, WorldPosition + GetForwardVector(), GetUpVector());
}

FMatrix RCameraComponent::GetProjectionMatrix() const
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine, {});

    auto Editor = Engine->GetEditor();
    RCheckReturn(Editor, {});

    auto Frame = Editor->GetFrame();
    RCheckReturn(Frame, {});

    const FIntVector FrameSize = Frame->GetFrameSize();
    const GLfloat FrameRatio = static_cast<GLfloat>(FrameSize.x) / static_cast<GLfloat>(FrameSize.y);
    
    return glm::perspective(glm::radians(FOV), FrameRatio, 0.1f, 100.0f);
}

void RCameraComponent::SetFOV(float InFOV)
{
    FOV = FMath::Clamp(InFOV, 0.001f, 179.99f);
}

float RCameraComponent::GetFOV() const
{
    return FOV;
}

void RCameraComponent::SetSpeed(float InSpeed)
{
    Speed = InSpeed;
}

float RCameraComponent::GetSpeed() const
{
    return Speed;
}
