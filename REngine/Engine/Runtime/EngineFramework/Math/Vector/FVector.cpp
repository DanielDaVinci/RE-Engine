#include "FVector.h"

#include "GLM/gtx/transform.hpp"

FMatrix FVector::GetTranslationMatrix() const
{
    return glm::translate(FMatrix(1.0f), *this);
}

FMatrix FVector::GetScaleMatrix() const
{
    return glm::scale(FMatrix(1.0f), *this);
}
