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
    static const FVector XVector;
    static const FVector YVector;
    static const FVector ZVector;

    FVector(const aiVector3D& AssimpVector);

    FMatrix GetTranslationMatrix() const;
    FMatrix GetScaleMatrix() const;
};
