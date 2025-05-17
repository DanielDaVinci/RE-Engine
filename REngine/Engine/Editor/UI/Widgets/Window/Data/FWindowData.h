#pragma once
#include <optional>
#include <string>

#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector2D.h"
#include "ThirdParty/ExternalIncludes/imGUI/imgui.h"

struct FWindowData
{
    std::string Name = "Default";

    FVector2D Position = FVector2D::ZeroVector;
    FVector2D Size = FVector2D::ZeroVector;

    std::optional<ImVec2> ForcePosition = std::nullopt;
    std::optional<ImVec2> ForceSize = std::nullopt;
    std::optional<ImGuiID> ForceViewport = std::nullopt;
    
    ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_None;
    ImGuiDockNodeFlags DockspaceFlags = ImGuiDockNodeFlags_None;

    float RoundingRadius = 0;
    float BorderSize = 0;
    ImVec2 PaddingSize = ImVec2(0.0f, 0.0f);
    
};
