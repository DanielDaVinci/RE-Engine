#pragma once
#include <string>

#include "assimp/scene.h"
#include "Core/Public/Object/RObject.h"
#include "REngine/Engine/Runtime/Engine/StatichMesh/FStaticMesh.h"

struct FTransform;

class RMesh : public RObject
{
public:
    using RObject::RObject;

    void Construct() override;

    void LoadMesh(const std::string& MeshPath);
    void Render(const FTransform& Transform, float DeltaTime);
    void RenderStroke(const FTransform& Transform, float DeltaTime);

    FBox CalcBoundingBox() const;
    FBox GetBoundingBox() const;
    
protected:
    FBox BoundingBox;
    
    void LoadAssimpNode(const aiNode* AssimpNode, const aiScene* AssimpScene);
    
    FStaticMesh LoadAssimpMesh(const aiMesh* AssimpMesh, const aiScene* AssimpScene);
    static std::vector<FVertex> LoadVerticesFromAssimpMesh(const aiMesh* AssimpMesh);
    static std::vector<unsigned int> LoadIndicesFromAssimpMesh(const aiMesh* AssimpMesh);
    std::vector<FTexture> LoadTexturesFromAssimpMesh(const aiMesh* AssimpMesh, const aiScene* AssimpScene);
    
    std::vector<FTexture> LoadTexturesFromAssimpMaterial(
        const aiMaterial* AssimpMaterial,
        const aiTextureType& Type,
        const std::string& TypeName);
    static GLuint LoadTextureFromFile(const std::string& Path, const std::string& Directory, bool gamma = false);
    
private:
    std::vector<FStaticMesh> StaticMeshes;
    std::vector<FTexture> LoadedTextures;
    std::string MeshDirectory;
    std::shared_ptr<FShader> Shader;
    std::shared_ptr<FShader> StrokeShader;
    
};
