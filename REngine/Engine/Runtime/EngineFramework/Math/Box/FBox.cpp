#include "FBox.h"

#include "REngine/Engine/Runtime/EngineFramework/Math/FMath.h"

FBox::FBox(const FVector& InMin, const FVector& InMax) : Min(InMin), Max(InMax)
{
    
}

FVector FBox::GetCenter() const
{
    return (Min + Max) * 0.5f;
}

FVector FBox::GetSize() const
{
    return Max - Min;
}

bool FBox::IsInside(const FVector& Point) const
{
    return Point >= Min && Point <= Max; 
}

void FBox::Expand(const FVector& Point)
{
    Min.x = FMath::Min(Min.x, Point.x);
    Min.y = FMath::Min(Min.y, Point.y);
    Min.z = FMath::Min(Min.z, Point.z);

    Max.x = FMath::Max(Max.x, Point.x);
    Max.y = FMath::Max(Max.y, Point.y);
    Max.z = FMath::Max(Max.z, Point.z);
}

FBox& FBox::operator+=(const FBox& OtherBox)
{
    Expand(OtherBox.Min);
    Expand(OtherBox.Max);
    return *this;
}

FBox operator*(const FMatrix& Matrix, const FBox& Box)
{
    FVector Corners[8] =
    {
        {Box.Min.x, Box.Min.y, Box.Min.z},
        {Box.Min.x, Box.Min.y, Box.Max.z},
        {Box.Min.x, Box.Max.y, Box.Min.z},
        {Box.Min.x, Box.Max.y, Box.Max.z},
        {Box.Max.x, Box.Min.y, Box.Min.z},
        {Box.Max.x, Box.Min.y, Box.Max.z},
        {Box.Max.x, Box.Max.y, Box.Min.z},
        {Box.Max.x, Box.Max.y, Box.Max.z}
    };

    FBox TransformedBox;
    for (const auto& Corner : Corners)
    {
        const FVector TransformedCorner = Matrix * Corner;
        TransformedBox.Expand(TransformedCorner);
    }

    return TransformedBox;
}
