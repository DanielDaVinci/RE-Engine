#include "FRotator.h"

#include "GLM/gtx/euler_angles.hpp"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

const FRotator FRotator::ZeroRotator = FRotator(0.0f, 0.0f, 0.0f);

FRotator::FRotator(const glm::vec3& Vector)
{
    *this = Vector;
}

void FRotator::SetPitch(float InPitch)
{
    x = InPitch;
}

float FRotator::GetPitch() const
{
    return x;
}

float FRotator::GetPitchRadians() const
{
    return glm::radians(x);
}

void FRotator::SetYaw(float InYaw)
{
    y = InYaw;
}

float FRotator::GetYaw() const
{
    return y;
}

float FRotator::GetYawRadians() const
{
    return glm::radians(y);
}

void FRotator::SetRoll(float InRoll)
{
    z = InRoll;
}

float FRotator::GetRoll() const
{
    return z;
}

float FRotator::GetRollRadians() const
{
    return glm::radians(z);
}

FMatrix FRotator::GetRotationMatrix() const
{
    return glm::eulerAngleYXZ(GetYawRadians(), GetPitchRadians(), GetRollRadians());
}
