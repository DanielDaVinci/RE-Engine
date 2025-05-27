#pragma once
#include <cmath>

class FMath
{
public:

    static bool IsNearlyEqual(float Left, float Right, float Tolerance = 1e-8f)
    {
        return Abs(Right - Left) < Tolerance;
    }

    static bool IsNearlyZero(float Value, float Tolerance = 1e-8f)
    {
        return IsNearlyEqual(Value, 0.0f, Tolerance);
    }

    static float Abs(float Value)
    {
        return fabs(Value);
    }
};
