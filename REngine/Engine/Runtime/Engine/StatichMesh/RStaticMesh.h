#pragma once

#include <vector>
#include "../MeshLibrary.h"

class FShader;

class RStaticMesh 
{
private:

	unsigned int VAO, VBO, EBO;

public:
	std::vector<FVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<FTexture> textures;

public:

	RStaticMesh(std::vector<FVertex> vertices = {}, std::vector<unsigned int> indices = {}, std::vector<FTexture> textures = {});

	void Draw(FShader shader);

private:

	void setupMesh();

};

