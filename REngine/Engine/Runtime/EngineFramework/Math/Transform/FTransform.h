#pragma once
#include "MetaReflection/MetaReflection.h"

#include "REngine/Engine/Runtime/EngineFramework/Math/Quat/FQuat.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"
#include "Generated/FTransform.generated.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Rotator/FRotator.h"

struct STRUCT() FTransform
{
    GENERATED_BODY()

    PROPERTY()
    FVector Position = FVector::ZeroVector;

    PROPERTY()
    FQuat Quaternion = FQuat::ZeroQuat;

    PROPERTY()
    FVector Scale = FVector::OneVector;

    FTransform() = default;
    FTransform(const FVector& InPosition, const FQuat& InQuaternion, const FVector& InScale = FVector::OneVector);
    explicit FTransform(const FMatrix& InMatrix);

    FMatrix GetMatrix() const;

    FTransform operator * (const FTransform& Other) const;
};

META_REFLECT()
