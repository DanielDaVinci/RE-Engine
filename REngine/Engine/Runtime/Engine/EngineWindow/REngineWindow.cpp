#include "REngineWindow.h"

#include "imGUI/imgui_impl_glfw.h"
#include "imGUI/imgui_impl_opengl3.h"

REngineWindow::~REngineWindow()
{
    Destroy();
}

void REngineWindow::Create(const FEngineWindowParameters& InWindowParameters)
{
    WindowParameters = InWindowParameters;
    
    glfwWindow = glfwCreateWindow(
        WindowParameters.Width,
        WindowParameters.Height,
        WindowParameters.Name.c_str(),
        NULL,                                   // TODO: add monitor for full screen
        NULL);
    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(WindowParameters.SwapInterval);
}

void REngineWindow::InitForOpenGL()
{
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void REngineWindow::Destroy()
{
    glfwDestroyWindow(glfwWindow);
}

bool REngineWindow::IsWindowShouldClose() const
{
    return glfwWindowShouldClose(glfwWindow);
}

void REngineWindow::SetWindowHint(GLint Hint, GLint Value)
{
    glfwWindowHint(Hint, Value);
}

void REngineWindow::SetWindowName(const std::string& Name)
{
    WindowParameters.Name = Name;
    glfwSetWindowTitle(glfwWindow, Name.c_str());
}

std::pair<int, int> REngineWindow::GetWindowSize() const
{
    GLint width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    return std::make_pair(width, height);
}

void REngineWindow::SetKeyCallback(GLFWkeyfun Callback) const
{
    glfwSetKeyCallback(glfwWindow, Callback);
}

void REngineWindow::SetMouseButtonCallback(GLFWmousebuttonfun Callback) const
{
    glfwSetMouseButtonCallback(glfwWindow, Callback);
}
