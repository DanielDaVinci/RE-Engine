#include "FVector.h"

#include "GLM/gtx/transform.hpp"

FVector::FVector(const aiVector3D& AssimpVector)
{
    x = AssimpVector.x;
    y = AssimpVector.y;
    z = AssimpVector.z;
}

FMatrix FVector::GetTranslationMatrix() const
{
    return glm::translate(FMatrix(1.0f), *this);
}

FMatrix FVector::GetScaleMatrix() const
{
    return glm::scale(FMatrix(1.0f), *this);
}
