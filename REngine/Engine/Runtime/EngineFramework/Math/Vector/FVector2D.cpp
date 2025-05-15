#include "FVector2D.h"

const FVector2D FVector2D::ZeroVector = FVector2D(0.0f, 0.0f);

FVector2D::FVector2D(const aiVector3D& Vector)
{
    x = Vector.x;
    y = Vector.y;
}
