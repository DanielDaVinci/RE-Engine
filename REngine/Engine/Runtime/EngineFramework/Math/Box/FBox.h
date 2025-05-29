#pragma once
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector.h"

class FBox
{
public:
    FVector Min = FVector::MaxVector;
    FVector Max = FVector::MinVector;

    FBox() = default;
    FBox(const FVector& InMin, const FVector& InMax);
    FBox(const FBox& box) = default;

    FVector GetCenter() const;
    FVector GetSize() const;
    bool IsInside(const FVector& Point) const;

    void Expand(const FVector& Point);
    FBox& operator+=(const FBox& OtherBox);
};

FBox operator * (const FMatrix& Matrix, const FBox& Box);
