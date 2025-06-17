#include "FShader.h"

#include "ThirdParty/ExternalIncludes/GLM/gtc/type_ptr.hpp"

FShader::FShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	setVertex(vertexPath);
	setFragment(fragmentPath);
	setProgram();
}

void FShader::setProgram()
{
	if (program != 0)
		glDeleteProgram(program);

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

GLuint FShader::getProgram() const
{
	return program;
}

std::string FShader::getVertexPath() const
{
	return vertexPath;
}

std::string FShader::getFragmentPath() const
{
	return fragmentPath;
}

void FShader::setVertex(const GLchar* path)
{
	vertexPath = (path == nullptr) ? "" : path;

	std::string vertexCode = getCodeFromFile(path);

	vertexShader = getShader(GL_VERTEX_SHADER, vertexCode.c_str());
}

void FShader::setFragment(const GLchar* path)
{
	fragmentPath = (path == nullptr) ? "" : path;

	std::string fragmentCode = getCodeFromFile(path);

	fragmentShader = getShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
}

void FShader::Use() const
{
	glUseProgram(program);
}

GLuint FShader::getUniformLocation(const GLchar* name) const
{
	return glGetUniformLocation(program, name);
}

void FShader::setUniform(const GLchar* name, const GLfloat value) const
{
	glUniform1f(getUniformLocation(name), value);
}

void FShader::setUniform(const GLchar* name, const GLint value) const
{
	glUniform1i(getUniformLocation(name), value);
}

void FShader::setUniform(const GLchar* name, const GLuint value) const
{
	glUniform1ui(getUniformLocation(name), value);
}

void FShader::setUniform(const GLchar* name, const GLfloat* value) const
{	
	glUniform4fv(getUniformLocation(name), sizeof(value) / sizeof(GLfloat), value);
}

void FShader::setUniform(const GLchar* name, glm::vec3 value) const
{
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void FShader::setUniform(const GLchar* name, glm::mat4 value) const
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

std::string FShader::getCodeFromFile(const GLchar* path)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		shaderFile.open((path == nullptr) ? "" : path);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	}
	catch (std::istream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode;
}

GLuint FShader::getShader(GLenum type, const GLchar* source)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	return shader;
}
