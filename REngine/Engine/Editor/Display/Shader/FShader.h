#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include "ThirdParty/ExternalIncludes/GL/glew.h"
#include "ThirdParty/ExternalIncludes/GLM/fwd.hpp"

class FShader
{
public:
	FShader(const GLchar* vertexPath = nullptr, const GLchar* fragmentPath = nullptr);
	
	void setProgram();
	GLuint getProgram() const;

	std::string getVertexPath() const;
	std::string getFragmentPath() const;

	void setVertex(const GLchar* path);
	void setFragment(const GLchar* path);

	void Use() const;

	GLuint getUniformLocation(const GLchar* name) const;
	void setUniform(const GLchar* name, const GLfloat value) const;
	void setUniform(const GLchar* name, const GLint value) const;
	void setUniform(const GLchar* name, const GLuint value) const;
	void setUniform(const GLchar* name, const GLfloat* value) const;
	void setUniform(const GLchar* name, glm::vec3 value) const;
	void setUniform(const GLchar* name, glm::mat4 value) const;

private:
	GLuint program = 0;

	std::string vertexPath;
	std::string fragmentPath;

	GLuint vertexShader;
	GLuint fragmentShader;

	static std::string getCodeFromFile(const GLchar* path);
	static GLuint getShader(GLenum type, const GLchar* source);

};

