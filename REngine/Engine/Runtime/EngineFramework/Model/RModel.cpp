#include "RModel.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "REngine/Engine/Editor/Display/Shader/FShader.h"
#include "REngine/Engine/Runtime/Engine/StatichMesh/FStaticMesh.h"
#include "SOIL/SOIL.h"

using namespace std;

RModel::RModel(string path)
{
	LoadModel(path);
}

void RModel::Draw(FShader shader)
{
	for (FStaticMesh& Mesh : StaticMeshes)
	{
		// Mesh.Draw(shader);
	}
}

void RModel::LoadModel(string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void RModel::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		StaticMeshes.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

FStaticMesh RModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<FVertex> vertices;
	vector<unsigned int> indices;
	vector<FTexture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		FVertex vertex;

		vertex.Position = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		vertex.Normal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoords = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<FTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<FTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return FStaticMesh(std::move(vertices), std::move(indices), std::move(textures));
}

vector<FTexture> RModel::LoadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName)
{
	vector<FTexture> textures;
	
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString path;
		material->GetTexture(type, i, &path);

		bool skip = false;

		for (const FTexture& FTexture : LoadedTextures)
		{
			if (strcmp(FTexture.Path.c_str(), path.C_Str()) == 0)
			{
				textures.push_back(FTexture);
				skip = true;
				break;
			}
		}

		if (skip)
		{
			continue;
		}

		textures.emplace_back(
			LoadTextureFromFile(path.C_Str(), directory),
			typeName,
			path.C_Str()
		);
		LoadedTextures.push_back(textures.back());
	}

	return textures;
}

unsigned int RModel::LoadTextureFromFile(const char* path, const string& directory, bool gamma)
{
	string filename = path;
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = SOIL_load_image(filename.c_str(), &width, &height, &nrComponents, 0);
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
		std::cout << "FTexture failed to load at path: " << path << std::endl;
	}

	SOIL_free_image_data(data);

	return textureID;
}