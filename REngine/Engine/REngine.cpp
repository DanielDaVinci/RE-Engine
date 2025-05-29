#include "REngine.h"

#include <memory>

#include "Editor/REditor.h"
#include "Runtime/Engine/EngineWindow/REngineWindow.h"
#include "Runtime/EngineFramework/Math/Vector/FVector2D.h"

std::shared_ptr<REngine> REngine::SingletonEngine = nullptr;

std::shared_ptr<REngine> REngine::GetEngine()
{
    if (!SingletonEngine)
    {
        SingletonEngine = NewObject<REngine>(nullptr);
    }

    return SingletonEngine;
}

bool REngine::IsEngineActive() const
{
    return bIsEngineActive;
}

void REngine::PreInitialize()
{
    
}

void REngine::Initialize()
{
    glfwInit();

    // Engine window
    FEngineWindowParameters WindowParameters;
    WindowParameters.Width = 1600;
    WindowParameters.Height = 1000;
    WindowParameters.bResizable = GL_TRUE;
    WindowParameters.bCursorVisibility = GLFW_CURSOR_NORMAL;
    WindowParameters.SwapInterval = 1;
    
    EngineWindow = NewObject<REngineWindow>();
    RCheckReturn(EngineWindow);
    
    EngineWindow->Create(WindowParameters);
    EngineWindow->SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    EngineWindow->SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    EngineWindow->SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glewExperimental = GL_TRUE;
    glewInit();
    
    SetWindowCallbacks();
    
    Editor = NewObject<REditor>();
    RCheckReturn(Editor);
    Editor->Initialize();
}

void REngine::PostInitialize()
{
    DeltaTime = 0;
    CurrentTickTime = 0;
    PreviousTickTime = 0;
    
    bIsEngineActive = true;
}

void REngine::PreTick()
{
    glfwPollEvents();
    
    PreviousTickTime = CurrentTickTime;
    CurrentTickTime = glfwGetTime();
    DeltaTime = CurrentTickTime - PreviousTickTime;

    Editor->PreTick(DeltaTime);
}

void REngine::Tick()
{
    RCheckReturn(Editor);

    // TODO: Debug FPS, Remove for Release
    static GLdouble PrevFPS = 0.0f;
    if (CurrentTickTime - PrevFPS > 1.0f)
    {
        PrevFPS = CurrentTickTime;
        RCheckReturn(EngineWindow);
        EngineWindow->SetWindowName(std::to_string(floor(1.0f / DeltaTime)));
    }
    
    Editor->Tick(DeltaTime);
}

void REngine::PostTick()
{
    glfwSwapBuffers(EngineWindow->glfwWindow);

    bIsEngineActive = !EngineWindow->IsWindowShouldClose();
}

void REngine::Exit()
{
    glfwTerminate();
}

std::shared_ptr<REditor> REngine::GetEditor() const
{
    return Editor;
}

std::shared_ptr<REngineWindow> REngine::GetEngineWindow() const
{
    return EngineWindow;
}

void REngine::SetWindowCallbacks()
{
    RCheckReturn(EngineWindow);
    EngineWindow->SetKeyCallback(&FCallbackWrapper::OnKeyCallback);
    EngineWindow->SetMouseButtonCallback(&FCallbackWrapper::OnMouseButtonCallback);
    EngineWindow->SetMouseMoveCallback(&FCallbackWrapper::OnMouseMoveCallback);
}

void REngine::FCallbackWrapper::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    const std::shared_ptr<REngine> Engine = REngine::GetEngine();
    RCheckReturn(Engine);
    
    Engine->OnKeyCallback(window, key, scancode, action, mode);
}

void REngine::FCallbackWrapper::OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    const std::shared_ptr<REngine> Engine = REngine::GetEngine();
    RCheckReturn(Engine);
    
    Engine->OnMouseButtonCallback(window, button, action, mods);
}

void REngine::FCallbackWrapper::OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    const std::shared_ptr<REngine> Engine = REngine::GetEngine();
    RCheckReturn(Engine);
    
    Engine->OnMouseMoveCallback(window, xpos, ypos);
}

void REngine::OnKeyCallback(GLFWwindow* Window, int key, int scancode, int action, int mode) const
{
    RCheckReturn(Editor);
    
    if (action == GLFW_PRESS)
    {
        Editor->OnKeyDown(key, scancode, mode);
    }
    else if (action == GLFW_RELEASE)
    {
        Editor->OnKeyUp(key, scancode, mode);
    }
}

void REngine::OnMouseButtonCallback(GLFWwindow* Window, int button, int action, int mods) const
{
    RCheckReturn(Editor);
    RCheckReturn(EngineWindow);
    
    if (action == GLFW_PRESS)
    {
        Editor->OnMouseDown(button, mods, EngineWindow->GetCursorPosition());
    }
    else if (action == GLFW_RELEASE)
    {
        Editor->OnMouseUp(button, mods, EngineWindow->GetCursorPosition());
    }
}

void REngine::OnMouseMoveCallback(GLFWwindow* Window, double XPosition, double YPosition) const
{
    RCheckReturn(Editor);
    Editor->OnMouseMove(FVector2D(XPosition, YPosition));
}
