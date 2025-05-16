#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Math/Quat/FQuat.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Rotator/FRotator.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

struct FTransform
{
    FVector Position = FVector::ZeroVector;
    FQuat Quaternion = FQuat();
    FRotator Rotation = FRotator::ZeroRotator;
    FVector Scale = FVector::OneVector;

    FTransform() = default;
    FTransform(const FVector& InPosition, const FRotator& InRotation, const FVector& InScale);
    FTransform(const FMatrix& InMatrix);

    FMatrix GetMatrix() const;

    FTransform operator * (const FTransform& Other) const;
};
