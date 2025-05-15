#pragma once
#include <string>

#include "assimp/scene.h"
#include "Core/Public/Object/RObject.h"
#include "REngine/Engine/Runtime/Engine/StatichMesh/RStaticMesh.h"

class RMesh : public RObject
{
public:
    using RObject::RObject;

    void LoadMesh(const std::string& MeshPath);
    void Render(float DeltaTime);
    
protected:
    void LoadAssimpNode(const aiNode* AssimpNode, const aiScene* AssimpScene);
    
    RStaticMesh LoadAssimpMesh(const aiMesh* AssimpMesh, const aiScene* AssimpScene);
    static std::vector<FVertex> LoadVerticesFromAssimpMesh(const aiMesh* AssimpMesh);
    static std::vector<unsigned int> LoadIndicesFromAssimpMesh(const aiMesh* AssimpMesh);
    std::vector<FTexture> LoadTexturesFromAssimpMesh(const aiMesh* AssimpMesh, const aiScene* AssimpScene);
    
    std::vector<FTexture> LoadTexturesFromAssimpMaterial(
        const aiMaterial* AssimpMaterial,
        const aiTextureType& Type,
        const std::string& TypeName);
    static GLuint LoadTextureFromFile(const std::string& Path, const std::string& Directory, bool gamma = false);
    
private:
    std::vector<RStaticMesh> StaticMeshes;
    std::vector<FTexture> LoadedTextures;
    std::string MeshDirectory;
    
};
