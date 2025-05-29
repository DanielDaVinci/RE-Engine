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
const FVector FVector::MaxVector = FVector(FLT_MAX);
const FVector FVector::MinVector = FVector(-FLT_MAX);

FVector::FVector(const glm::vec3& Vector)
{
    *this = Vector;
}

FVector::FVector(const glm::vec4& Vector)
{
    *this = glm::vec3(Vector);
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

FVector& FVector::operator=(const glm::vec4& Vector)
{
    *this = glm::vec3(Vector);
    return *this;
}

bool FVector::operator>=(const FVector& OtherVector) const
{
    return x >= OtherVector.x && y >= OtherVector.y && z >= OtherVector.z;
}

bool FVector::operator>(const FVector& OtherVector) const
{
    return x > OtherVector.x && y > OtherVector.y && z > OtherVector.z;
}

bool FVector::operator<=(const FVector& OtherVector) const
{
    return x <= OtherVector.x && y <= OtherVector.y && z <= OtherVector.z;
}

bool FVector::operator<(const FVector& OtherVector) const
{
    return x < OtherVector.x && y < OtherVector.y && z < OtherVector.z;
}

FVector::operator glm::vec4() const
{
    return glm::vec4(*this, 1.0f);
}
