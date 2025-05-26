#pragma once
#include "Core/Public/Object/RObject.h"
#include "Data/FEngineWindowParameters.h"

struct FVector2D;

class REngineWindow : public RObject
{
    friend class REngine;
    
public:
    using RObject::RObject;
    
    ~REngineWindow() override;

    void Create(const FEngineWindowParameters& InWindowParameters);
    void InitForOpenGL();
    void Destroy();

    bool IsWindowShouldClose() const;
    
    static void SetWindowHint(GLint Hint, GLint Value);
    void SetWindowName(const std::string& Name);
    
    void SetInputMode(int mode, int value) const;
    void EnableCursor() const;
    void DisableCursor() const;
    void HiddenCursor() const;
    
    std::pair<int, int> GetWindowSize() const;
    FVector2D GetCursorPosition() const;
    
protected:
    void SetKeyCallback(GLFWkeyfun Callback) const;
    void SetMouseButtonCallback(GLFWmousebuttonfun Callback) const;
    void SetMouseMoveCallback(GLFWcursorposfun Callback) const;

private:
    GLFWwindow* glfwWindow = nullptr;
    FEngineWindowParameters WindowParameters;
    
};
