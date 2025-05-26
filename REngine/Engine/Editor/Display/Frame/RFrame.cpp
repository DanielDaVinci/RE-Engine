#include "RFrame.h"
#include "../Shader/FShader.h"

void RFrame::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
}

void RFrame::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RFrame::Draw(FShader shader)
{
    shader.Use();
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, ColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RFrame::SetFrameSize(GLuint InWidth, GLuint InHeight)
{
    Width = InWidth;
    Height = InHeight;

    glBindTexture(GL_TEXTURE_2D, ColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, InWidth, InHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorBuffer, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, InWidth, InHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RFrame::SetFrameSize(std::pair<GLuint, GLuint> InSize)
{
    SetFrameSize(InSize.first, InSize.second);
}

std::pair<GLuint, GLuint> RFrame::GetFrameSize() const
{
    return { Width, Height };
}

GLuint RFrame::getTextureID()
{
    return ColorBuffer;
}

void RFrame::Construct()
{
    RObject::Construct();

    glGenFramebuffers(1, &FrameBuffer);
    Bind();
    {
        GenerateColorBuffer();
        GenerateRBO();
    }
    UnBind();

    GenerateFrameTexture();
}

void RFrame::GenerateColorBuffer()
{
    glGenTextures(1, &ColorBuffer);
    glBindTexture(GL_TEXTURE_2D, ColorBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorBuffer, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void RFrame::GenerateRBO()
{
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 0, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RFrame::GenerateFrameTexture()
{
    float vertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
