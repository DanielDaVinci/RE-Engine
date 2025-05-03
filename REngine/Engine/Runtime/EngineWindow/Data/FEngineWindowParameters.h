#pragma once

#define GLEW_STATIC

#include <string>

#include "ThirdParty/ExternalIncludes/GL/glew.h"
#include "ThirdParty/ExternalIncludes/GLFW/glfw3.h"

struct FEngineWindowParameters
{
    std::string Name;
    
    GLuint Width = 0, Height = 0;
    GLint X = 0, Y = 0;

    GLint bResizable = GL_TRUE;
    GLint bCursorVisibility = GLFW_CURSOR_NORMAL;

    GLint SwapInterval = 1;
};
