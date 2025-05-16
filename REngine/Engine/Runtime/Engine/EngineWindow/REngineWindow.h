#pragma once
#include "Core/Public/Object/RObject.h"
#include "Data/FEngineWindowParameters.h"

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
    std::pair<int, int> GetWindowSize() const;

protected:
    void SetKeyCallback(GLFWkeyfun Callback) const;
    void SetMouseButtonCallback(GLFWmousebuttonfun Callback) const;

private:
    GLFWwindow* glfwWindow = nullptr;
    FEngineWindowParameters WindowParameters;
    
};
