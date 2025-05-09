#include "FTransform.h"

#include "GLM/gtx/rotate_normalized_axis.hpp"

FTransform::FTransform() : Position(), Rotation(), Scale()
{
}

FTransform::FTransform(const FVector& InPosition, const FRotator& InRotation, const FVector& InScale)
    : Position(InPosition), Rotation(InRotation), Scale(InScale)
{
}

FTransform::FTransform(const FMatrix& InMatrix)
{
    Position = FVector(InMatrix[3]);
    Scale = FVector{
        glm::length(InMatrix[0]),
        glm::length(InMatrix[1]),
        glm::length(InMatrix[2]),
    };

    glm::mat3 RotationMatrix;
    RotationMatrix[0] = InMatrix[0] / Scale[0];
    RotationMatrix[1] = InMatrix[1] / Scale[1];
    RotationMatrix[2] = InMatrix[2] / Scale[2];
    
    Rotation = glm::degrees(glm::eulerAngles(glm::quat_cast(RotationMatrix)));
}

FMatrix FTransform::GetMatrix() const
{
    return Position.GetTranslationMatrix() * Rotation.GetRotationMatrix() * Scale.GetScaleMatrix();
}

FTransform FTransform::operator*(const FTransform& Other) const
{
    return FMatrix(GetMatrix() * Other.GetMatrix());
}
