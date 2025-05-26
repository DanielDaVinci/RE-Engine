#include "FQuat.h"

#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"
#include "REngine/Engine/Runtime/EngineFramework/Math/Rotator/FRotator.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

const FQuat FQuat::ZeroQuat = FQuat(0.0f, 0.0f, 0.0f);

FQuat::FQuat(const glm::quat& InQuat)
{
    *this = InQuat;
}

FQuat::FQuat(float Pitch, float Yaw, float Roll)
{
    *this =
        glm::angleAxis(glm::radians(Yaw), FVector::UpVector)
        * glm::angleAxis(glm::radians(Pitch), FVector::RightVector)
        * glm::angleAxis(glm::radians(Roll), FVector::ForwardVector);
}

FQuat::FQuat(const FRotator& InRotator) : FQuat(InRotator.GetPitch(), InRotator.GetYaw(), InRotator.GetRoll())
{
}

void FQuat::SetPitch(float Pitch)
{
    *this = FQuat(Pitch, GetYaw(), GetRoll());
}

float FQuat::GetPitch() const
{
    return GetEulerAngles().x;
}

void FQuat::AddPitch(float Pitch)
{
    *this *= glm::angleAxis(glm::radians(Pitch), FVector::RightVector);
}

void FQuat::AddWorldPitch(float Pitch)
{
    *this = glm::angleAxis(glm::radians(Pitch), FVector::RightVector) * *this;
}

void FQuat::SetYaw(float Yaw)
{
    *this = FQuat(GetPitch(), Yaw, GetRoll());
}

float FQuat::GetYaw() const
{
    return GetEulerAngles().y;
}

void FQuat::AddYaw(float Yaw)
{
    *this *= glm::angleAxis(glm::radians(Yaw), FVector::UpVector);
}

void FQuat::AddWorldYaw(float Yaw)
{
    *this = glm::angleAxis(glm::radians(Yaw), FVector::UpVector) * *this;
}

void FQuat::SetRoll(float Roll)
{
    *this = FQuat(GetPitch(), GetYaw(), Roll);
}

float FQuat::GetRoll() const
{
    return GetEulerAngles().z;
}

void FQuat::AddRoll(float Roll)
{
    *this *= glm::angleAxis(glm::radians(Roll), FVector::ForwardVector);
}

void FQuat::AddWorldRoll(float Roll)
{
    *this = glm::angleAxis(glm::radians(Roll), FVector::ForwardVector) * *this;
}

FVector FQuat::GetEulerAngles() const
{
    // const glm::vec3 Angles = glm::degrees(glm::eulerAngles(*this));
    return glm::degrees(glm::eulerAngles(*this));
}

FMatrix FQuat::GetMatrix() const
{
    return glm::toMat4(*this);
}
