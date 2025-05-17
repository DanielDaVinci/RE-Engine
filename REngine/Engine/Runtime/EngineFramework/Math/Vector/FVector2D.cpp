#include "FVector2D.h"
#include <iostream>

const FVector2D FVector2D::ZeroVector = FVector2D(0.0f, 0.0f);

FVector2D::FVector2D(const aiVector3D& Vector)
{
    x = Vector.x;
    y = Vector.y;
}

FVector2D::FVector2D(const glm::vec2& Vector)
{
    *this = Vector;
}

FVector2D::FVector2D(const ImVec2& Vector)
{
    x = Vector.x;
    y = Vector.y;
}

std::ostream& operator<<(std::ostream& os, const FVector2D& Vector)
{
    os << Vector.x;
    return os << "(X: " << Vector.x << "; Y: " << Vector.y << ")";
}
