#include "FQuat.h"

#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

FQuat::FQuat(float Pitch, float Yaw, float Roll)
{
    *this = glm::angleAxis(Yaw, FVector::YVector)
        * glm::angleAxis(Pitch, FVector::XVector)
        * glm::angleAxis(Roll, FVector::ZVector);
}

void FQuat::SetPitch(float Pitch)
{
    *this = FQuat(Pitch, GetYaw(), GetRoll());
}

float FQuat::GetPitch() const
{
    return GetEulerAngles().x;
}

void FQuat::SetYaw(float Yaw)
{
    *this = FQuat(GetPitch(), Yaw, GetRoll());
}

float FQuat::GetYaw() const
{
    return GetEulerAngles().y;
}

void FQuat::SetRoll(float Roll)
{
    *this = FQuat(GetPitch(), GetYaw(), Roll);
}

float FQuat::GetRoll() const
{
    return GetEulerAngles().z;
}

FVector FQuat::GetEulerAngles() const
{
    const glm::vec3 Angles = glm::degrees(glm::eulerAngles(*this));
    return {Angles.x, Angles.y, Angles.z};
}

FMatrix FQuat::GetMatrix() const
{
    return glm::toMat4(*this);
}
