#pragma once

template <std::derived_from<RWidget> T>
std::shared_ptr<T> RContainerWidget::AddWidget()
{
    std::shared_ptr<RWidget> Widget = NewObject<T>();
    RCheckReturn(Widget, nullptr);
    Widget->SetEditor(GetEditor());
    AddChild(Widget);
    
    return std::static_pointer_cast<T>(Widget);
}