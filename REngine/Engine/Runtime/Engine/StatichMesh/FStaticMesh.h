#pragma once

#include <memory>
#include <vector>

#include "REngine/Engine/Runtime/Engine/MeshLibrary.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Box/FBox.h"

class FShader;

class FStaticMesh 
{
public:
	FStaticMesh(std::vector<FVertex>&& InVertices = {}, std::vector<unsigned int>&& InIndices = {}, std::vector<FTexture>&& InTextures = {});
	FStaticMesh(const std::vector<FVertex>& InVertices = {}, const std::vector<unsigned int>& InIndices = {}, const std::vector<FTexture>& InTextures = {});

	void Render(const std::shared_ptr<FShader>& Shader) const;

	FBox CalcBoundingBox() const;
	FBox GetBoundingBox() const;

private:
	unsigned int VAO, VBO, EBO;
	std::vector<FVertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<FTexture> Textures;

	FBox BoundingBox;

	void UpdateBuffers();

};

