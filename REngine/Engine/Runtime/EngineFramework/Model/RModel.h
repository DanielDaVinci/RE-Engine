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
	RModel(std::string path);

	void Draw(FShader shader);

protected:
	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	RStaticMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<FTexture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	unsigned int LoadTextureFromFile(const char* path, const std::string& directory, bool gamma = false);
	
private:
	std::vector<RStaticMesh> StaticMeshes;
	std::vector<FTexture> LoadedTextures;
	std::string directory;

};
