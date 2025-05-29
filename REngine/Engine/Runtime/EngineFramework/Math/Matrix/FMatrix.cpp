#include "FMatrix.h"

FMatrix::FMatrix(const glm::mat4& Matrix) : glm::mat4(Matrix)
{
}

FMatrix FMatrix::GetInverse() const
{
    return glm::inverse(*this);
}
