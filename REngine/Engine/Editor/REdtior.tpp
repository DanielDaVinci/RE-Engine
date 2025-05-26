#pragma once

template <std::derived_from<RSubsystem> T>
std::shared_ptr<T> REditor::GetSubsystem()
{
    const std::string& SubsystemClassName = typeid(T).name();
    if (!Subsystems.contains(SubsystemClassName))
    {
        Subsystems[SubsystemClassName] = NewObject<T>();
    }

    return std::static_pointer_cast<T>(Subsystems[SubsystemClassName]);
}