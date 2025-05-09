#pragma once
#include "GLM/fwd.hpp"
#include "glm/vec3.hpp"
#include "REngine/Engine/Runtime/EngineFramework/Math/Matrix/FMatrix.h"

struct FVector : public glm::vec3
{
    using glm::vec3::vec3;
    using glm::vec3::operator=;

    FMatrix GetTranslationMatrix() const;
    FMatrix GetScaleMatrix() const;
};
