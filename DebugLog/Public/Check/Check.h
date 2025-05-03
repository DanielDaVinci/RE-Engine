#pragma once

#include <csignal>

#ifdef _WIN32
#define TRAP_SIGNAL SIGABRT
#else
#include <signal.h>
#define TRAP_SIGNAL SIGTRAP
#endif

#define RCheck(Condition)   \
    (Condition ||           \
    []()                    \
    {                       \
        raise(TRAP_SIGNAL); \
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