#pragma once
#include "glm/fwd.hpp"
#include "glm/detail/type_quat.hpp"

struct FVector;
struct FMatrix;

struct FQuat : public glm::quat
{
    using glm::quat::quat;
    using glm::quat::operator=;

    FQuat(float Pitch, float Yaw, float Roll);

    void SetPitch(float Pitch);
    float GetPitch() const;

    void SetYaw(float Yaw);
    float GetYaw() const;

    void SetRoll(float Roll);
    float GetRoll() const;

    FVector GetEulerAngles() const;
    FMatrix GetMatrix() const;
};
