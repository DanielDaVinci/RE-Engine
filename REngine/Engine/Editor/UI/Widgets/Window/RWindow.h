#pragma once
#include <string>

#include "Data/FWindowData.h"
#include "REngine/Engine/Editor/UI/Widgets/ContainerWidget/RContainerWidget.h"

class RWindow : public RContainerWidget
{
public:
    explicit RWindow(const std::shared_ptr<RObject>& InOwner);
    ~RWindow() override;

    static void SetForcePosition(const ImVec2& Position);
    static void SetForceSize(const ImVec2& Size);
    static void SetForceViewport(const ImGuiID& ViewportID);

    void SetWindowFlags(const ImGuiWindowFlags& Flags);
    void SetRounding(float Radius);
    void SetBorderSize(float Size);
    void SetPaddingSize(const ImVec2& PaddingSize);

    virtual bool IsNeedDockspace() const;

    void Init(const std::shared_ptr<REditor>& InEditor) override;
    void Draw() override;

protected:
    void SetWindowName(const std::string& Name);
    std::string GetWindowName() const;

    void AddWindowStyle(ImGuiStyleVar StyleIndex, float Value);
    void AddWindowStyle(ImGuiStyleVar StyleIndex, const ImVec2& Value);
    virtual void PushWindowStyle();
    virtual void PopWindowStyle();
    
    virtual void InitDockspace();
    virtual void DrawWindowContent() const;

    
private:
    FWindowData WindowData;
    int WindowStyleNums;
    
};
