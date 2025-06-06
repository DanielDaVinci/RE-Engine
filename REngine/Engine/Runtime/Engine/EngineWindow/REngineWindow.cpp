#include "REngineWindow.h"

#include "imGUI/imgui_impl_glfw.h"
#include "imGUI/imgui_impl_opengl3.h"
#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector2D.h"

REngineWindow::~REngineWindow()
{
    Destroy();
}

std::shared_ptr<REngineWindow> REngineWindow::GetEngineWindow()
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine, {});

    return Engine->GetEngineWindow();
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

void REngineWindow::SetInputMode(int mode, int value) const
{
    glfwSetInputMode(glfwWindow, mode, value);
}

void REngineWindow::EnableCursor() const
{
    SetInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void REngineWindow::DisableCursor() const
{
    SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void REngineWindow::HiddenCursor() const
{
    SetInputMode(GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

std::pair<int, int> REngineWindow::GetWindowSize() const
{
    GLint width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    return std::make_pair(width, height);
}

FVector2D REngineWindow::GetCursorPosition() const
{
    double XPosition, YPosition;
    glfwGetCursorPos(glfwWindow, &XPosition, &YPosition);

    return FVector2D(XPosition, YPosition);
}

void REngineWindow::SetKeyCallback(GLFWkeyfun Callback) const
{
    glfwSetKeyCallback(glfwWindow, Callback);
}

void REngineWindow::SetMouseButtonCallback(GLFWmousebuttonfun Callback) const
{
    glfwSetMouseButtonCallback(glfwWindow, Callback);
}

void REngineWindow::SetMouseMoveCallback(GLFWcursorposfun Callback) const
{
    glfwSetCursorPosCallback(glfwWindow, Callback);
}
