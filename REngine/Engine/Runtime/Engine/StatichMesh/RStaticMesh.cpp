#include "RStaticMesh.h"

#include <sstream>

#include "GL/glew.h"
#include "REngine/Engine/Editor/Display/Shader/FShader.h"

using namespace std;

RStaticMesh::RStaticMesh(vector<FVertex>&& InVertices, vector<unsigned int>&& InIndices, vector<FTexture>&& InTextures)
    : Vertices(std::move(InVertices)), Indices(std::move(InIndices)), Textures(std::move(InTextures))
{
	UpdateBuffers();
}

RStaticMesh::RStaticMesh(const std::vector<FVertex>& InVertices, const std::vector<unsigned int>& InIndices, const std::vector<FTexture>& InTextures)
    : Vertices(InVertices), Indices(InIndices), Textures(InTextures)
{
    UpdateBuffers();
}


void RStaticMesh::Render(const std::shared_ptr<FShader>& Shader) const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        stringstream ss;
        string number;
        string name = Textures[i].Type;
        if (name == "texture_diffuse")
        {
            number = to_string(diffuseNr++);
        }
        else if (name == "texture_specular")
        {
            number = to_string(specularNr++);
        }


        Shader->setUniform(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, Textures[i].Id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RStaticMesh::UpdateBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(FVertex), Vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)offsetof(FVertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)offsetof(FVertex, TexCoords));

    glBindVertexArray(0);
}
