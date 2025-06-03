#pragma once

template<typename T>
static constexpr void RDetailsView::DrawValuesFromReflection(T* Value)
{
    constexpr auto TypeInfo = refl::reflect<T>();
    refl::util::for_each(TypeInfo.members, [&](auto member)
    {
        std::string MemberName = member.name.str();
            
        auto& MemberValue = member.get(*Value);
        using MemberType = std::decay_t<decltype(MemberValue)>;
            
        if constexpr (std::is_same_v<MemberType, int>)
        {
            ImGui::SliderInt(MemberName.c_str(), &MemberValue, -100, 100);
        }
        else if constexpr (std::is_same_v<MemberType, float>)
        {
            ImGui::SliderFloat(MemberName.c_str(), &MemberValue, -100.0f, 100.0f);
        }
        else if constexpr (std::is_same_v<MemberType, bool>)
        {
            ImGui::Checkbox(MemberName.c_str(), &MemberValue);
        }
        else if constexpr (std::is_same_v<MemberType, FVector>)
        {
            ImGui::SliderFloat3(MemberName.c_str(), &MemberValue.x, -100.0f, 100.0f);
        }
        else if constexpr (std::is_same_v<MemberType, FQuat>)
        {
            if (ImGui::SliderFloat3(MemberName.c_str(), &MemberValue.EditorPitch, -180.0f, 180.0f))
            {
                MemberValue.OnEditorValueChanged();
            }
        }
        else if constexpr (refl::trait::is_reflectable_v<MemberType>)
        {
            if (ImGui::TreeNodeEx(MemberName.c_str(), ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen))
            {
                RDetailsView::DrawValuesFromReflection(&MemberValue);
                ImGui::TreePop();
            }
        }
    });
}