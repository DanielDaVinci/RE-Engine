#pragma once

#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Editor/REditor.h"

template <std::derived_from<RSubsystem> T>
std::shared_ptr<T> RSubsystem::GetSubsystem()
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine, nullptr);

    auto Editor = Engine->GetEditor();
    RCheckReturn(Editor, nullptr);

    return Editor->GetSubsystem<T>();
}
