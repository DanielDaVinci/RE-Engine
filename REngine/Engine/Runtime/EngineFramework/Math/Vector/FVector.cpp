#include "FVector.h"

#include "GLM/gtx/transform.hpp"

const FVector FVector::ZeroVector = FVector(0.0f, 0.0f, 0.0f);
const FVector FVector::OneVector = FVector(1.0f, 1.0f, 1.0f);
const FVector FVector::XVector = FVector(1.0f, 0.0f, 0.0f);
const FVector FVector::YVector = FVector(0.0f, 1.0f, 0.0f);
const FVector FVector::ZVector = FVector(0.0f, 0.0f, 1.0f);

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
