#pragma once
#include "GLM/mat4x4.hpp"

struct FMatrix : public glm::mat4
{
    using glm::mat4::mat4;
    using glm::mat4::operator=;

    FMatrix(const glm::mat4& Matrix);
};
