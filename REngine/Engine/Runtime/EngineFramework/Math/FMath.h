#pragma once
#include <cmath>

#include "GLM/common.hpp"

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
    
    template<typename T>
    static T Min(const T& Left, const T& Right)
    {
        return Left < Right ? Left : Right;
    }

    template<typename T>
    static T Max(const T& Left, const T& Right)
    {
        return Left > Right ? Left : Right;
    }

    template<typename T>
    static T Clamp(const T& Value, const T& Min, const T& Max)
    {
        return glm::max(glm::min(Value, Max), Min);
    }
};
