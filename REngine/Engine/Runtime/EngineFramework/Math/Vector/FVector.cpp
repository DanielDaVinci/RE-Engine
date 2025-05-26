#include "FVector.h"

#include "GLM/gtx/transform.hpp"

const FVector FVector::ZeroVector = FVector(0.0f, 0.0f, 0.0f);
const FVector FVector::OneVector = FVector(1.0f, 1.0f, 1.0f);
const FVector FVector::ForwardVector = FVector(1.0f, 0.0f, 0.0f);
const FVector FVector::BackwardVector = FVector(-1.0f, 0.0f, 0.0f);
const FVector FVector::RightVector = FVector(0.0f, 1.0f, 0.0f);
const FVector FVector::LeftVector = FVector(0.0f, -1.0f, 0.0f);
const FVector FVector::UpVector = FVector(0.0f, 0.0f, 1.0f);
const FVector FVector::DownVector = FVector(0.0f, 0.0f, -1.0f);

FVector::FVector(const glm::vec3& Vector)
{
    *this = Vector;
}

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
