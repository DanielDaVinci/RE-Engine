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

    StrokeShader = std::make_shared<FShader>("Data/Shaders/strokeShader.vs", "Data/Shaders/strokeShader.frag");
    RCheckReturn(StrokeShader);
    
}

void RMesh::LoadMesh(const std::string& MeshPath)
{
    Assimp::Importer Importer;

    unsigned int ImporterFlags = aiProcess_Triangulate;
    if (MeshPath != "Content/objects/backpack/backpack.obj")
    {
        ImporterFlags |= aiProcess_FlipUVs;
    }
    
    const aiScene* AssimpScene = Importer.ReadFile(MeshPath, ImporterFlags);
    RCheckReturn(AssimpScene);
    RCheckReturn(AssimpScene->mRootNode);
    RCheckReturn(!(AssimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE));

    MeshDirectory = MeshPath.substr(0, MeshPath.find_last_of('/'));

    LoadAssimpNode(AssimpScene->mRootNode, AssimpScene);
    BoundingBox = CalcBoundingBox();
}

void RMesh::Render(const FTransform& Transform, bool bIsSelected, float DeltaTime)
{
    RCheckReturn(Shader);
    RCheckReturn(REngine::GetEngine());

    auto Editor = REngine::GetEngine()->GetEditor();
    RCheckReturn(Editor);

    std::shared_ptr<RCameraComponent> Camera = REditor::GetCamera();
    RCheckReturn(Camera);

    auto CameraPosition = Camera->GetWorldPosition();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    Shader->Use();
    Shader->setUniform("pointLight.position", FVector(0.0f, 0.0f, 25.0f));
    Shader->setUniform("pointLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("pointLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("pointLight.constant", 1.0f);
    Shader->setUniform("pointLight.linear", 0.05f);
    Shader->setUniform("pointLight.constant", 0.05f);
    Shader->setUniform("viewPos", CameraPosition);
    
    Shader->setUniform("model", Transform.GetMatrix());
    Shader->setUniform("view", Camera->GetViewMatrix());
    Shader->setUniform("projection", Camera->GetProjectionMatrix());
    Shader->setUniform("bIsSelected", bIsSelected);
    
    for (const FStaticMesh& StaticMesh : StaticMeshes)
    {
        StaticMesh.Render(Shader);
    }
}

void RMesh::RenderStroke(const FTransform& Transform, float DeltaTime)
{
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00); 
    glDisable(GL_DEPTH_TEST);
    
    RCheckReturn(Shader);
    RCheckReturn(REngine::GetEngine());

    auto Editor = REngine::GetEngine()->GetEditor();
    RCheckReturn(Editor);

    auto Camera = REditor::GetCamera();
    RCheckReturn(Camera);
    
    StrokeShader->Use();
    StrokeShader->setUniform("model", Transform.GetMatrix());
    StrokeShader->setUniform("view", Camera->GetViewMatrix());
    StrokeShader->setUniform("projection", Camera->GetProjectionMatrix());

    for (const FStaticMesh& StaticMesh : StaticMeshes)
    {
        StaticMesh.Render(StrokeShader);
    }

    glStencilFunc(GL_ALWAYS, 1, 0xFF); 
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
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
        GLenum InternalFormat;
        GLenum DataFormat;
        if (Channels == 1)
        {
            InternalFormat = DataFormat = GL_RED;
        }
        else if (Channels == 3)
        {
            InternalFormat = gamma ? GL_SRGB : GL_RGB;
            DataFormat = GL_RGB;
        }
        else if (Channels == 4)
        {
            InternalFormat = gamma ? GL_SRGB_ALPHA : GL_RGBA;
            DataFormat = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, DataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    SOIL_free_image_data(data);

    return TextureID;
}
