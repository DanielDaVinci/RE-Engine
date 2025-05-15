#pragma once

#include <memory>
#include <vector>
#include "../MeshLibrary.h"

class FShader;

class RStaticMesh 
{
public:
	RStaticMesh(std::vector<FVertex>&& InVertices = {}, std::vector<unsigned int>&& InIndices = {}, std::vector<FTexture>&& InTextures = {});
	RStaticMesh(const std::vector<FVertex>& InVertices = {}, const std::vector<unsigned int>& InIndices = {}, const std::vector<FTexture>& InTextures = {});

	void Render(const std::shared_ptr<FShader>& Shader) const;

private:
	unsigned int VAO, VBO, EBO;
	std::vector<FVertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<FTexture> Textures;

	void UpdateBuffer();

};

