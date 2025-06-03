#include "REditor.h"

#include <string>


#include "DebugLog/Public/Check/Check.h"
#include "Display/Frame/RFrame.h"
#include "Display/Shader/FShader.h"
#include "glm/detail/type_quat.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtc/quaternion.hpp"
#include "REngine/Engine/REngine.h"
#include "REngine/Engine/Runtime/Engine/EngineWindow/REngineWindow.h"
#include "REngine/Engine/Runtime/Engine/Mesh/RMesh.h"
#include "REngine/Engine/Runtime/EngineFramework/Actor/RActor.h"
#include "REngine/Engine/Runtime/EngineFramework/Camera/RCameraLegacy.h"
#include "REngine/Engine/Runtime/EngineFramework/Camera/RCameraSubsystem.h"
#include "REngine/Engine/Runtime/EngineFramework/Components/CameraComponent/RCameraComponent.h"
#include "REngine/Engine/Runtime/EngineFramework/Model/RModel.h"
#include "REngine/Engine/Runtime/EngineFramework/Scene/RScene.h"
#include "ThirdParty/ExternalIncludes/GLFW/glfw3.h"
#include "ThirdParty/ExternalIncludes/GLM/fwd.hpp"
#include "ThirdParty/ExternalIncludes/GLM/vec3.hpp"
#include "ThirdParty/ExternalIncludes/GLM/ext/matrix_transform.hpp"
#include "ThirdParty/ExternalIncludes/imGUI/imgui.h"
#include "ThirdParty/ExternalIncludes/imGUI/imgui_impl_glfw.h"
#include "ThirdParty/ExternalIncludes/imGUI/imgui_impl_opengl3.h"
#include "UI/Widgets/RootWindow/RRootWindow.h"

std::shared_ptr<REditor> REditor::GetEngineEditor()
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine, {});

    return Engine->GetEditor();
}

void REditor::Initialize()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    io.FontGlobalScale = 1.1f; // Scale text
    ImGui::GetStyle().ScaleAllSizes(1.1f);
    
    ImGui::StyleColorsDark();

    std::shared_ptr<REngineWindow> EngineWindow = GetEngineWindow();
    RCheckReturn(EngineWindow);
    EngineWindow->InitForOpenGL();
    
    RootWidget = NewObject<RRootWindow>();
    RCheckReturn(RootWidget);
    RootWidget->Initialize(GetSharedThis<REditor>());

    Scene = NewObject<RScene>();
    RCheckReturn(Scene);
    Scene->Initialize();
    
    Frame = NewObject<RFrame>();
    RCheckReturn(Frame);
    Frame->SetFrameSize(EngineWindow->GetWindowSize());
    
    FrameShader = std::make_shared<FShader>("Data/Shaders/frameShader.vs", "Data/Shaders/frameShader.frag");
}

void REditor::Tick(GLdouble DeltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    if (RCheck(Scene))
    {
        Scene->Tick(DeltaTime);
    }
    if (RCheck(RootWidget))
    {
        RootWidget->Tick(DeltaTime);
    }

    ImGui::NewFrame();
    DrawMainMenuBar();
    DrawUI(DeltaTime);
    ImGui::EndFrame();

    ImGui::Render();
    
    PreRender(DeltaTime);
    Render(DeltaTime);
    PostRender(DeltaTime);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void REditor::PreRender(GLdouble DeltaTime)
{
    Frame->Bind();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glDepthFunc(GL_LESS);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glStencilMask(0x00);

    if (RCheck(Scene))
    {
        Scene->PreRender(DeltaTime);
    }
}

void REditor::Render(GLdouble DeltaTime)
{
    if (RCheck(Scene))
    {
        Scene->Render(DeltaTime);
    }
}

void REditor::PostRender(GLdouble DeltaTime)
{
    Frame->UnBind();
}

void REditor::DrawUI(GLdouble DeltaTime)
{
    if (RCheck(RootWidget))
    {
        RootWidget->Draw();
    }

    ImGui::ShowDebugLogWindow();
}

void REditor::DrawMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Import file"))
            {
                
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void REditor::OnKeyDown(int Key, int Scancode, int Mode)
{
    Keys[Key] = GL_TRUE;
    if (RCheck(RootWidget))
    {
        RootWidget->OnKeyDown(Key, Scancode, Mode);
    }
}

void REditor::OnKeyUp(int Key, int Scancode, int Mode)
{
    Keys[Key] = GL_FALSE;
    if (RCheck(RootWidget))
    {
        RootWidget->OnKeyUp(Key, Scancode, Mode);
    }
}

void REditor::OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition)
{
    MouseButtons[Button] = GL_TRUE;
    if (RCheck(RootWidget))
    {
        RootWidget->OnMouseDown(Button, Mods, CursorPosition);
    }
}

void REditor::OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition)
{
    MouseButtons[Button] = GL_FALSE;
    if (RCheck(RootWidget))
    {
        RootWidget->OnMouseUp(Button, Mods, CursorPosition);
    }
}

void REditor::OnMouseMove(const FVector2D& CursorPosition)
{
    if (RCheck(RootWidget))
    {
        RootWidget->OnMouseMove(CursorPosition);
    }
}

std::shared_ptr<REngineWindow> REditor::GetEngineWindow()
{
    auto Engine = REngine::GetEngine();
    RCheckReturn(Engine, {});

    return Engine->GetEngineWindow();
}

std::shared_ptr<RFrame> REditor::GetFrame() const
{
    return Frame;
}

std::shared_ptr<RScene> REditor::GetScene() const
{
    return Scene;
}

std::shared_ptr<RCameraComponent> REditor::GetCamera()
{
    auto CameraSubsystem = RCameraSubsystem::Get();
    RCheckReturn(CameraSubsystem, {});
    
    return CameraSubsystem->GetSelectedCamera();
}

std::pair<GLint, GLint> REditor::GetGLFWWindowSize(GLFWwindow* window)
{
    GLint width, height;
    glfwGetFramebufferSize(window, &width, &height);
    return std::make_pair(width, height);
}

void REditor::Exit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void REditor::PreTick(GLdouble DeltaTime)
{
}
