#pragma once

#include <vector>
#include <string>

#include "REngine/Engine/Runtime/Engine/MeshLibrary.h"
#include "REngine/Engine/Runtime/Engine/StatichMesh/RStaticMesh.h"
#include "ThirdParty/ExternalIncludes/assimp/material.h"


struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiNode;
class FShader;

class RModel
{
public:

	std::vector<RStaticMesh> meshes;

    std::vector<Texture> textures_load;

	std::string directory;

public:
	RModel(std::string path);

	void Draw(FShader shader);

private:

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	RStaticMesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

};
