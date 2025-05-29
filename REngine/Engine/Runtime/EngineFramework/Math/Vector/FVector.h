#pragma once

#include "assimp/vector3.h"
#include "GLM/fwd.hpp"
#include "glm/vec3.hpp"
#include "REngine/Engine/Runtime/EngineFramework/Math/Matrix/FMatrix.h"

struct FVector : public glm::vec3
{
    using glm::vec3::vec3;
    using glm::vec3::operator=;

    static const FVector ZeroVector;
    static const FVector OneVector;
    static const FVector ForwardVector;
    static const FVector BackwardVector;
    static const FVector RightVector;
    static const FVector LeftVector;
    static const FVector UpVector;
    static const FVector DownVector;
    static const FVector MaxVector;
    static const FVector MinVector;

    FVector(const glm::vec3& Vector);
    FVector(const glm::vec4& Vector);
    FVector(const aiVector3D& AssimpVector);

    FMatrix GetTranslationMatrix() const;
    FMatrix GetScaleMatrix() const;

    FVector& operator = (const glm::vec4& Vector);
    bool operator >= (const FVector& OtherVector) const;
    bool operator > (const FVector& OtherVector) const;
    bool operator <= (const FVector& OtherVector) const;
    bool operator < (const FVector& OtherVector) const;
    operator glm::vec4() const;
};
