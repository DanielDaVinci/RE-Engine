#include "RDirectLightComponent.h"

#include "REngine/Engine/Editor/Display/Shader/FShader.h"

void RDirectLightComponent::ApplyLightData(const std::shared_ptr<FShader>& Shader, int Index)
{
    RCheckReturn(Shader);

    Shader->setUniform("dirLight.direction", GetWorldRotation() * FVector::ForwardVector);
    Shader->setUniform("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
}

void RDirectLightComponent::Construct()
{
    RLightComponent::Construct();

    ShadowShader = std::make_shared<FShader>("Data/Shaders/ShadowShader.vs", "Data/Shaders/ShadowShader.frag");
    RCheckReturn(ShadowShader);

    glGenFramebuffers(1, &ShadowMapFBO);
    
    glGenTextures(1, &ShadowMap);
    glBindTexture(GL_TEXTURE_2D, ShadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 static_cast<GLint>(ShadowMapSize.x), static_cast<GLint>(ShadowMapSize.y),
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
}

FMatrix RDirectLightComponent::GetViewMatrix() const
{
    const FVector WorldPosition = GetWorldPosition();
    return glm::lookAt(WorldPosition, WorldPosition + GetForwardVector(), GetUpVector());
}

FMatrix RDirectLightComponent::GetProjectionMatrix() const
{
    return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NearPlaneDistance, FarPlaneDistance);
}
