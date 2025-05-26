#pragma once

#define GLEW_STATIC
#include "Core/Public/Object/RObject.h"
#include "ThirdParty/ExternalIncludes/GL/glew.h"

class FShader;

class RFrame : public RObject
{
public:
	using RObject::RObject;

	void Bind();
	void UnBind();
	void Draw(FShader shader);
	
	void SetFrameSize(GLuint InWidth, GLuint InHeight);
	void SetFrameSize(std::pair<GLuint, GLuint> InSize);
	std::pair<GLuint, GLuint> GetFrameSize() const;

	GLuint getTextureID();

protected:
	void Construct() override;

private:
	GLuint Width, Height;

	GLuint FrameBuffer;
	GLuint ColorBuffer;

	GLuint RBO;
	GLuint VAO, VBO;
	
	void GenerateColorBuffer();
	void GenerateRBO();
	void GenerateFrameTexture();

};

