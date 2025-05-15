#pragma once
#include "GLM/fwd.hpp"
#include "GLM/vec3.hpp"

struct FMatrix;

struct FRotator : public glm::vec3
{
    using glm::vec3::vec3;
    using glm::vec3::operator=;

    void SetPitch(float InPitch);
    float GetPitch() const;
    
    void SetYaw(float InYaw);
    float GetYaw() const;
    
    void SetRoll(float InRoll);
    float GetRoll() const;
    
    FMatrix GetRotationMatrix() const;
};
