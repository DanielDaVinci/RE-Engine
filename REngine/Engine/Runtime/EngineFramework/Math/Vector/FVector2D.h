#pragma once
#include "FVector.h"
#include "glm/vec2.hpp"

struct FVector2D : public glm::vec2
{
    using glm::vec2::vec2;
    using glm::vec2::operator=;

    static const FVector2D ZeroVector;

    FVector2D(const aiVector3D& Vector);
};


