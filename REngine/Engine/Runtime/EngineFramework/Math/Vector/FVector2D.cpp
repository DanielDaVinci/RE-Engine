#include "FVector2D.h"

FVector2D::FVector2D(const aiVector3D& Vector)
{
    x = Vector.x;
    y = Vector.y;
}
