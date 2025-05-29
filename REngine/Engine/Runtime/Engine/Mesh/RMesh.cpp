#include "RMesh.h"

#include <iostream>
#include <SOIL/SOIL.h>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "DebugLog/Public/Check/Check.h"
#include "GLM/trigonometric.hpp"
#include "GLM/gtx/transform.hpp"
#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Editor/REditor.h"
#include "REngine/Engine/Editor/Display/Shader/FShader.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/CameraComponent/RCameraComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/FMath.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Transform/FTransform.h"

void RMesh::Construct()
{
    RObject::Construct();

    Shader = std::make_shared<FShader>("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");
    RCheckReturn(Shader);
}

void RMesh::LoadMesh(const std::string& MeshPath)
{
    Assimp::Importer Importer;
    
    const aiScene* AssimpScene = Importer.ReadFile(MeshPath, aiProcess_Triangulate); // aiProcess_FlipUVs
    RCheckReturn(AssimpScene);
    RCheckReturn(AssimpScene->mRootNode);
    RCheckReturn(!(AssimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE));

    MeshDirectory = MeshPath.substr(0, MeshPath.find_last_of('/'));

    LoadAssimpNode(AssimpScene->mRootNode, AssimpScene);
    BoundingBox = CalcBoundingBox();
}

void RMesh::Render(const FTransform& Transform, float DeltaTime)
{
    RCheckReturn(Shader);
    RCheckReturn(REngine::GetEngine());

    auto Editor = REngine::GetEngine()->GetEditor();
    RCheckReturn(Editor);

    auto Camera = REditor::GetCamera();
    RCheckReturn(Camera);

    auto CameraPosition = Camera->GetWorldPosition();
    
    Shader->Use();
    Shader->setUniform("pointLight.position", CameraPosition);
    Shader->setUniform("pointLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    Shader->setUniform("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    Shader->setUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("pointLight.constant", 1.0f);
    Shader->setUniform("pointLight.linear", 0.22f);
    Shader->setUniform("pointLight.constant", 0.20f);
    Shader->setUniform("viewPos", CameraPosition);
    
    Shader->setUniform("model", Transform.GetMatrix());
    Shader->setUniform("view", Camera->GetViewMatrix());
    Shader->setUniform("projection", Camera->GetProjectionMatrix());
    
    for (const FStaticMesh& StaticMesh : StaticMeshes)
    {
        StaticMesh.Render(Shader);
    }
}

FBox RMesh::CalcBoundingBox() const
{
    FBox Bound;
    for (const FStaticMesh& StaticMesh : StaticMeshes)
    {
        Bound += StaticMesh.GetBoundingBox();
    }

    return Bound;
}

FBox RMesh::GetBoundingBox() const
{
    return BoundingBox;
}

void RMesh::LoadAssimpNode(const aiNode* AssimpNode, const aiScene* AssimpScene)
{
    for (unsigned int i = 0; i < AssimpNode->mNumMeshes; i++)
    {
        StaticMeshes.push_back(LoadAssimpMesh(AssimpScene->mMeshes[AssimpNode->mMeshes[i]], AssimpScene));
    }

    for (unsigned int i = 0; i < AssimpNode->mNumChildren; i++)
    {
        LoadAssimpNode(AssimpNode->mChildren[i], AssimpScene);
    }
}

FStaticMesh RMesh::LoadAssimpMesh(const aiMesh* AssimpMesh, const aiScene* AssimpScene)
{
    return FStaticMesh(
        LoadVerticesFromAssimpMesh(AssimpMesh),
        LoadIndicesFromAssimpMesh(AssimpMesh),
        LoadTexturesFromAssimpMesh(AssimpMesh, AssimpScene));
}

std::vector<FVertex> RMesh::LoadVerticesFromAssimpMesh(const aiMesh* AssimpMesh)
{
    std::vector<FVertex> Vertices;
    Vertices.reserve(AssimpMesh->mNumVertices);
    
    for (unsigned int i = 0; i < AssimpMesh->mNumVertices; i++)
    {
        FVertex vertex;

        vertex.Position = AssimpMesh->mVertices[i];
        vertex.Normal = AssimpMesh->mNormals[i];

        if (AssimpMesh->mTextureCoords[0])
        {
            vertex.TexCoords = AssimpMesh->mTextureCoords[0][i];
        }
        else
        {
            vertex.TexCoords = FVector2D::ZeroVector;
        }

        Vertices.push_back(vertex);
    }

    return Vertices;
}

std::vector<unsigned int> RMesh::LoadIndicesFromAssimpMesh(const aiMesh* AssimpMesh)
{
    std::vector<unsigned int> Indices;
    
    for (unsigned int i = 0; i < AssimpMesh->mNumFaces; i++)
    {
        const aiFace& Face = AssimpMesh->mFaces[i];
        for (unsigned int j = 0; j < Face.mNumIndices; j++)
        {
            Indices.push_back(Face.mIndices[j]);
        }
    }

    return Indices;
}

std::vector<FTexture> RMesh::LoadTexturesFromAssimpMesh(const aiMesh* AssimpMesh, const aiScene* AssimpScene)
{
    std::vector<FTexture> Textures;
    
    if (AssimpMesh->mMaterialIndex < 0)
    {
        return Textures;
    }

    const aiMaterial* material = AssimpScene->mMaterials[AssimpMesh->mMaterialIndex];

    const std::vector<FTexture> DiffuseTextures = LoadTexturesFromAssimpMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
    Textures.insert(Textures.end(), DiffuseTextures.begin(), DiffuseTextures.end());

    const std::vector<FTexture> SpecularTextures = LoadTexturesFromAssimpMaterial(material, aiTextureType_SPECULAR, "texture_specular");
    Textures.insert(Textures.end(), SpecularTextures.begin(), SpecularTextures.end());

    return Textures;
}

std::vector<FTexture> RMesh::LoadTexturesFromAssimpMaterial(
    const aiMaterial* AssimpMaterial,
    const aiTextureType& Type,
    const std::string& TypeName)
{
    std::vector<FTexture> Textures;
    Textures.reserve(AssimpMaterial->GetTextureCount(Type));
	
    for (unsigned int i = 0; i < AssimpMaterial->GetTextureCount(Type); i++)
    {
        aiString AssimpPath;
        AssimpMaterial->GetTexture(Type, i, &AssimpPath);
        std::string Path = AssimpPath.C_Str();

        bool skip = false;

        for (const FTexture& Texture : LoadedTextures)
        {
            if (Texture.Path == Path)
            {
                Textures.push_back(Texture);
                skip = true;
                break;
            }
        }

        if (skip)
        {
            continue;
        }

        Textures.emplace_back(
            LoadTextureFromFile(Path, MeshDirectory),
            TypeName,
            Path
        );
        LoadedTextures.push_back(Textures.back());
    }

    return Textures;
}

GLuint RMesh::LoadTextureFromFile(const std::string& Path, const std::string& Directory, bool gamma)
{
    const std::string Fullpath = Directory + '/' + Path;

    unsigned int TextureID;
    glGenTextures(1, &TextureID);

    int Width, Height, Channels;
    unsigned char* data = SOIL_load_image(Fullpath.c_str(), &Width, &Height, &Channels, 0);
    if (RCheck(data))
    {
        GLenum format;
        if (Channels == 1)
        {
            format = GL_RED;
        }
        else if (Channels == 3)
        {
            format = GL_RGB;
        }
        else if (Channels == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, Width, Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    SOIL_free_image_data(data);

    return TextureID;
}
