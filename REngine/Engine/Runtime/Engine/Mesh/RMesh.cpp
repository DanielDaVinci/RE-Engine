#include "RMesh.h"

#include <iostream>
#include <SOIL/SOIL.h>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "DebugLog/Public/Check/Check.h"

void RMesh::LoadMesh(const std::string& MeshPath)
{
    Assimp::Importer Importer;
    
    const aiScene* AssimpScene = Importer.ReadFile(MeshPath, aiProcess_Triangulate | aiProcess_FlipUVs);
    RCheckReturn(AssimpScene);
    RCheckReturn(AssimpScene->mRootNode);
    RCheckReturn(!(AssimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE));

    MeshDirectory = MeshPath.substr(0, MeshPath.find_last_of('/'));

    LoadAssimpNode(AssimpScene->mRootNode, AssimpScene);
}

void RMesh::Render(float DeltaTime)
{
    
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

RStaticMesh RMesh::LoadAssimpMesh(const aiMesh* AssimpMesh, const aiScene* AssimpScene)
{
    std::vector<FVertex> Vertices = LoadVerticesFromAssimpMesh(AssimpMesh);
    std::vector<unsigned int> Indices = LoadIndicesFromAssimpMesh(AssimpMesh);
    std::vector<FTexture> Textures = LoadTexturesFromAssimpMesh(AssimpMesh, AssimpScene);

    return RStaticMesh(Vertices, Indices, Textures);
}

std::vector<FVertex> RMesh::LoadVerticesFromAssimpMesh(const aiMesh* AssimpMesh)
{
    std::vector<FVertex> Vertices;
    
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
    std::string Fullpath = Path;
    Fullpath = Directory + '/' + Path;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = SOIL_load_image(Fullpath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << Path << std::endl;
    }

    SOIL_free_image_data(data);

    return textureID;
}
