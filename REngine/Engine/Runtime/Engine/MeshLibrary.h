#pragma once

#include <string>

#include "ThirdParty/ExternalIncludes/assimp/types.h"
#include "ThirdParty/ExternalIncludes/GLM/vec2.hpp"
#include "ThirdParty/ExternalIncludes/GLM/vec3.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    aiString path;
};