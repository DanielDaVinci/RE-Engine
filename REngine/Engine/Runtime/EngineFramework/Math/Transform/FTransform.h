#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Math/FRotator/FRotator.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

struct FTransform
{
    FVector Position;
    FRotator Rotation;
    FVector Scale;

    FTransform();
    FTransform(const FVector& InPosition, const FRotator& InRotation, const FVector& InScale);
    FTransform(const FMatrix& InMatrix);

    FMatrix GetMatrix() const;

    FTransform operator * (const FTransform& Other) const;
};
