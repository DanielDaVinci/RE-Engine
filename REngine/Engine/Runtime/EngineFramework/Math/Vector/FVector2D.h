#pragma once
#include "FVector.h"
#include "glm/vec2.hpp"

struct FVector2D : public glm::vec2
{
    using glm::vec2::vec2;
    using glm::vec2::operator=;

    static constexpr FVector2D ZeroVector = glm::vec2{0.0f, 0.0f};

    FVector2D(const aiVector3D& Vector);
};

