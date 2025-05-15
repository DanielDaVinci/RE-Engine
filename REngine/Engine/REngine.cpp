#include "REngine.h"

#include <memory>

#include "Editor/REditor.h"
#include "Runtime/EngineWindow/REngineWindow.h"

std::shared_ptr<REngine> REngine::SingletonEngine = nullptr;
REngine* REngine::FCallbackWrapper::StaticEngine = nullptr;

REngine::REngine(const std::shared_ptr<RObject>& InOwner) : RObject(InOwner)
{
    
}

REngine::~REngine()
{
}

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
    
    EngineWindow = std::make_shared<REngineWindow>(WindowParameters);
    EngineWindow->Create();

    EngineWindow->SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    EngineWindow->SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    EngineWindow->SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glewExperimental = GL_TRUE;
    glewInit();
    
    SetWindowCallbacks();

    // Engine editor
    Editor = NewObject<REditor>();
    RCheckReturn(Editor);
    Editor->Initialize(EngineWindow->glfwWindow);
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
    Editor->Tick(DeltaTime);
}

void REngine::PostTick()
{
    glfwSwapBuffers(EngineWindow->glfwWindow);

    bIsEngineActive = !EngineWindow->IsWindowShouldClose();
}

void REngine::Exit()
{
    EngineWindow->Destroy();
    glfwTerminate();
}

std::shared_ptr<REditor> REngine::GetEditor() const
{
    return Editor;
}

void REngine::SetWindowCallbacks()
{
    FCallbackWrapper::StaticEngine = this;
    EngineWindow->SetKeyCallback(&FCallbackWrapper::OnKeyCallback);
    EngineWindow->SetMouseButtonCallback(&FCallbackWrapper::OnMouseButtonCallback);
}

void REngine::FCallbackWrapper::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    StaticEngine->OnKeyCallback(window, key, scancode, action, mode);
}

void REngine::FCallbackWrapper::OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    StaticEngine->OnMouseButtonCallback(window, button, action, mods);
}

void REngine::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) const
{
    if (action == GLFW_PRESS)
    {
        Editor->OnKeyDown(key, scancode, mode);
    }
    else if (action == GLFW_RELEASE)
    {
        Editor->OnKeyUp(key, scancode, mode);
    }
}

void REngine::OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) const
{
    if (action == GLFW_PRESS)
    {
        Editor->OnMouseDown(button, mods);
    }
    else if (action == GLFW_RELEASE)
    {
        Editor->OnMouseUp(button, mods);
    }
}
