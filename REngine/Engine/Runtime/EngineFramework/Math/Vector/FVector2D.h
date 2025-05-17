#pragma once
#include <iosfwd>

#include "FVector.h"
#include "glm/vec2.hpp"
#include "imGUI/imgui.h"

struct FVector2D : public glm::vec2
{
    using glm::vec2::vec2;
    using glm::vec2::operator=;

    static const FVector2D ZeroVector;

    FVector2D(const aiVector3D& Vector);
    FVector2D(const glm::vec2& Vector);
    FVector2D(const ImVec2& Vector);

    friend std::ostream& operator<<(std::ostream& os, const FVector2D& Vector);
};


