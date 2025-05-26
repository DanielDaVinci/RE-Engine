#pragma once
#include "glm/fwd.hpp"
#include "glm/detail/type_quat.hpp"

struct FVector;
struct FRotator;
struct FMatrix;

struct FQuat : public glm::quat
{
    using glm::quat::quat;
    using glm::quat::operator=;

    static const FQuat ZeroQuat;

    FQuat(const glm::quat& InQuat);
    FQuat(float Pitch, float Yaw, float Roll);
    FQuat(const FRotator& InRotator);

    void SetPitch(float Pitch);
    float GetPitch() const;
    void AddPitch(float Pitch);
    void AddWorldPitch(float Pitch);

    void SetYaw(float Yaw);
    float GetYaw() const;
    void AddYaw(float Yaw);
    void AddWorldYaw(float Yaw);

    void SetRoll(float Roll);
    float GetRoll() const;
    void AddRoll(float Roll);
    void AddWorldRoll(float Roll);

    FVector GetEulerAngles() const;
    FMatrix GetMatrix() const;
};
