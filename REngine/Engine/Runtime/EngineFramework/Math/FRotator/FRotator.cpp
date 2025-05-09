#include "FRotator.h"

#include "GLM/gtx/euler_angles.hpp"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

void FRotator::SetPitch(float InPitch)
{
    x = InPitch;
}

float FRotator::GetPitch() const
{
    return x;
}

void FRotator::SetYaw(float InYaw)
{
    y = InYaw;
}

float FRotator::GetYaw() const
{
    return y;
}

void FRotator::SetRoll(float InRoll)
{
    z = InRoll;
}

float FRotator::GetRoll() const
{
    return z;
}

FMatrix FRotator::GetRotationMatrix() const
{
    return glm::eulerAngleXYZ(GetPitch(), GetYaw(), GetRoll());
}
