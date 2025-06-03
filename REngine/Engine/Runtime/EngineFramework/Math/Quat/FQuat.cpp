#include "FQuat.h"

#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"
#include "REngine/Engine/Runtime/EngineFramework/Math/Rotator/FRotator.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

const FQuat FQuat::ZeroQuat = FQuat(0.0f, 0.0f, 0.0f);

FQuat::FQuat(const glm::quat& InQuat)
{
    *this = InQuat;
}

FQuat::FQuat(float Pitch, float Yaw, float Roll)
{
    *this = glm::normalize(
        glm::angleAxis(glm::radians(Yaw), FVector::UpVector)
        * glm::angleAxis(glm::radians(Pitch), FVector::RightVector)
        * glm::angleAxis(glm::radians(Roll), FVector::ForwardVector));

    UpdateEditorAngles();
}

void FQuat::SetPitch(float Pitch)
{
    *this = FQuat(Pitch, GetYaw(), GetRoll());
}

float FQuat::GetPitch() const
{
    return GetEulerAngles().y;
}

void FQuat::AddPitch(float Pitch)
{
    *this = *this * glm::angleAxis(glm::radians(Pitch), FVector::RightVector);
    UpdateEditorAngles();
}

void FQuat::AddWorldPitch(float Pitch)
{
    *this = glm::angleAxis(glm::radians(Pitch), FVector::RightVector) * *this;
    UpdateEditorAngles();
}

void FQuat::SetYaw(float Yaw)
{
    *this = FQuat(GetPitch(), Yaw, GetRoll());
}

float FQuat::GetYaw() const
{
    return GetEulerAngles().z;
}

void FQuat::AddYaw(float Yaw)
{
    *this = glm::normalize(*this * glm::angleAxis(glm::radians(Yaw), FVector::UpVector));
    UpdateEditorAngles();
}

void FQuat::AddWorldYaw(float Yaw)
{
    *this = glm::normalize(glm::angleAxis(glm::radians(Yaw), FVector::UpVector) * *this);
    UpdateEditorAngles();
}

void FQuat::SetRoll(float Roll)
{
    *this = FQuat(GetPitch(), GetYaw(), Roll);
}

float FQuat::GetRoll() const
{
    return GetEulerAngles().x;
}

void FQuat::AddRoll(float Roll)
{
    *this = glm::normalize(*this * glm::angleAxis(glm::radians(Roll), FVector::ForwardVector));
    UpdateEditorAngles();
}

void FQuat::AddWorldRoll(float Roll)
{
    *this = glm::normalize(glm::angleAxis(glm::radians(Roll), FVector::ForwardVector) * *this);
    UpdateEditorAngles();
}

FVector FQuat::GetEulerAngles() const
{
    return glm::degrees(glm::eulerAngles(*this));
}

FMatrix FQuat::GetMatrix() const
{
    return glm::toMat4(*this);
}

void FQuat::UpdateEditorAngles()
{
    EditorPitch = GetPitch();
    EditorYaw = GetYaw();
    EditorRoll = GetRoll();
}

void FQuat::OnEditorValueChanged()
{
    *this = FQuat(EditorPitch, EditorYaw, EditorRoll);
}
