#pragma once

#include "DebugLog/Private/Check/RCheckValidator.h"

#define RCheck(Condition)   \
    (RCheckValidator<decltype(Condition)>::IsValid(Condition) ||           \
    []()                    \
    {                       \
        __debugbreak();     \
        return false;       \
    }())

#define RCheckReturn(Condition, ...)       \
    if (!RCheck(Condition))                \
        return __VA_ARGS__;                \
    else                                   \
        volatile auto __stub = ((void*)0)

#define RCheckContinue(Condition)          \
    if (!RCheck(Condition))                \
        continue;                          \
    else                                   \
        volatile auto __stub = ((void*)0)

#define RCheckBreak(Condition)             \
    if (!RCheck(Condition))                \
        break;                             \
    else                                   \
        volatile auto __stub = ((void*)0)