#pragma once
#include "GLM/fwd.hpp"
#include "GLM/vec3.hpp"

struct FMatrix;

struct FRotator : public glm::vec3
{
    using glm::vec3::vec3;
    using glm::vec3::operator=;

    static const FRotator ZeroRotator;

    FRotator(const glm::vec3& Vector);

    void SetPitch(float InPitch);
    float GetPitch() const;
    float GetPitchRadians() const;
    
    void SetYaw(float InYaw);
    float GetYaw() const;
    float GetYawRadians() const;
    
    void SetRoll(float InRoll);
    float GetRoll() const;
    float GetRollRadians() const;
    
    FMatrix GetRotationMatrix() const;
};
