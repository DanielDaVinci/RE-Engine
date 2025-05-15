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
#include "REngine/Engine/Runtime/EngineFramework/Camera/RCamera.h"

void RMesh::LoadMesh(const std::string& MeshPath)
{
    Assimp::Importer Importer;
    
    const aiScene* AssimpScene = Importer.ReadFile(MeshPath, aiProcess_Triangulate); // aiProcess_FlipUVs
    RCheckReturn(AssimpScene);
    RCheckReturn(AssimpScene->mRootNode);
    RCheckReturn(!(AssimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE));

    MeshDirectory = MeshPath.substr(0, MeshPath.find_last_of('/'));
    
    Shader = std::make_shared<FShader>("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");
    RCheckReturn(Shader);

    LoadAssimpNode(AssimpScene->mRootNode, AssimpScene);
}

void RMesh::Render(float DeltaTime)
{
    RCheckReturn(Shader);
    RCheckReturn(REngine::GetEngine());

    auto Editor = REngine::GetEngine()->GetEditor();
    RCheckReturn(Editor);

    auto Camera = Editor->GetCamera();
    RCheckReturn(Camera);
    
    Shader->Use();
    Shader->setUniform("pointLight.position", Camera->getPosition());
    Shader->setUniform("pointLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    Shader->setUniform("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    Shader->setUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("pointLight.constant", 1.0f);
    Shader->setUniform("pointLight.linear", 0.22f);
    Shader->setUniform("pointLight.constant", 0.20f);
    Shader->setUniform("viewPos", Camera->getPosition());

    glm::mat4 model(1.0f);
    
    model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Shader->setUniform("model", model);
    Shader->setUniform("view", Camera->getViewMatrix());
    Shader->setUniform("projection", Camera->getProjectionMatrix());
    
    for (const RStaticMesh& StaticMesh : StaticMeshes)
    {
        StaticMesh.Render(Shader);
    }
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
    return RStaticMesh(
        LoadVerticesFromAssimpMesh(AssimpMesh),
        LoadIndicesFromAssimpMesh(AssimpMesh),
        LoadTexturesFromAssimpMesh(AssimpMesh, AssimpScene));
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
