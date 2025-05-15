#pragma once

#include <string>

#include "GL/glew.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector2D.h"

struct FVertex
{
    FVector Position;
    FVector Normal;
    FVector2D TexCoords;
};

struct FTexture
{
    GLuint Id;
    std::string Type;
    std::string Path;
};