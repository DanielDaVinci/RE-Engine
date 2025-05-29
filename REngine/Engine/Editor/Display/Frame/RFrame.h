#pragma once

#define GLEW_STATIC
#include "Core/Public/Object/RObject.h"
#include "ThirdParty/ExternalIncludes/GL/glew.h"

struct FIntVector;
struct FVector2D;
class FShader;

struct FPixel
{
	union 
	{
		struct 
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};
		unsigned char rgba[4];
	};

	FPixel() = default;

	bool IsVoid() const;
};

class RFrame : public RObject
{
public:
	using RObject::RObject;

	void Bind();
	void UnBind();
	void Draw(FShader shader);
	
	void SetFrameSize(GLuint InWidth, GLuint InHeight);
	void SetFrameSize(std::pair<GLuint, GLuint> InSize);
	FIntVector GetFrameSize() const;

	GLuint GetTextureID() const;

	FPixel GetPixelAt(const FVector2D& Position) const;
	float GetDepthAt(const FVector2D& Position) const;

protected:
	void Construct() override;

private:
	bool bIsBinded = false;
	GLuint Width, Height;

	GLuint FrameBuffer;
	GLuint ColorBuffer;

	GLuint RBO;
	GLuint VAO, VBO;
	
	void GenerateColorBuffer();
	void GenerateRBO();
	void GenerateFrameTexture();

};

