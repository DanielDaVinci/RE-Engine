#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ThirdParty/ExternalIncludes/GL/glew.h"
#include "ThirdParty/ExternalIncludes/GLM/fwd.hpp"

#define GLEW_STATIC

using namespace std;

class FShader
{
private:

	GLuint program = 0;

	string vertexPath;
	string fragmentPath;

	GLuint vertexShader;
	GLuint fragmentShader;

public:

	FShader(const GLchar* vertexPath = nullptr, const GLchar* fragmentPath = nullptr);
	
	void setProgram();
	GLuint getProgram() const;

	string getVertexPath() const;
	string getFragmentPath() const;

	void setVertex(const GLchar* path);
	void setFragment(const GLchar* path);

	void Use();

	GLuint getUniformLocation(const GLchar* name);
	void setUniform(const GLchar* name, const GLfloat value);
	void setUniform(const GLchar* name, const GLint value);
	void setUniform(const GLchar* name, const GLuint value);
	void setUniform(const GLchar* name, const GLfloat* value);
	void setUniform(const GLchar* name, glm::vec3 value);
	void setUniform(const GLchar* name, glm::mat4 value);

private:

	static string getCodeFromFile(const GLchar* path);
	static GLuint getShader(GLenum type, const GLchar* source);

};

