#include "FTransform.h"

#include "GLM/gtx/euler_angles.hpp"
#include "GLM/gtx/matrix_decompose.hpp"
#include "GLM/gtx/rotate_normalized_axis.hpp"
#include "GLM/gtx/rotate_vector.hpp"

FTransform::FTransform(const FVector& InPosition, const FQuat& InQuaternion, const FVector& InScale)
    : Position(InPosition), Quaternion(InQuaternion), Scale(InScale)
{
}

FTransform::FTransform(const FMatrix& InMatrix)
{
    glm::vec3 DecomposeScale;
    glm::quat DecomposeRotation;
    glm::vec3 DecomposeTranslation;
    glm::vec3 DecomposeSkew;
    glm::vec4 DecomposePerspective;
    
    if (glm::decompose(InMatrix, DecomposeScale, DecomposeRotation, DecomposeTranslation, DecomposeSkew, DecomposePerspective))
    {
        Position = DecomposeTranslation;
        Quaternion = DecomposeRotation;
        Scale = DecomposeScale;
        return;
    }

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

    Quaternion = glm::quat_cast(RotationMatrix);
}

FMatrix FTransform::GetMatrix() const
{
    return Position.GetTranslationMatrix() * Quaternion.GetMatrix() * Scale.GetScaleMatrix();
}

FTransform FTransform::operator*(const FTransform& Other) const
{
    return FMatrix(GetMatrix() * Other.GetMatrix());
}
