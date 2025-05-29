#pragma once
#include "glm/vec3.hpp"

struct FIntVector : public glm::ivec3
{
public:
    using glm::ivec3::ivec3;
    using glm::ivec3::operator=;

    FIntVector(const glm::ivec3& Vector);
    
};
