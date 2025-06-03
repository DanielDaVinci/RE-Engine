#pragma once
#include "REngine/Engine/Editor/UI/Widgets/Window/RWindow.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Quat/FQuat.h"

class RActorComponent;
class RActor;

class RDetailsView : public RWindow
{
public:
    using RWindow::RWindow;
    
protected:
    void Construct() override;
    void DrawWindowContent() const override;
    void DrawActorProperties(const std::shared_ptr<RActor>& Actor) const;
    void DrawComponentProperties(const std::shared_ptr<RActorComponent>& Component) const;

    template<typename T>
    static constexpr void DrawValuesFromReflection(T* Value);
};

#include "RDetailsView.tpp"
