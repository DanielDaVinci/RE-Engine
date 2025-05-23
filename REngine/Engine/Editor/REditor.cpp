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
#include "REngine/Engine/Runtime/EngineFramework/Camera/RCamera.h"
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

REditor::REditor(const std::shared_ptr<RObject>& InOwner) : RObject(InOwner)
{
    
}

REditor::~REditor()
{
}

void REditor::Initialize()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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

    ScreenCamera = std::make_shared<RCamera>(800, 600, 45.0f);
    ScreenCamera->setAngle({ 0.0f, 0.0f, 0.0f });
}

void REditor::Tick(GLdouble DeltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    if (RCheck(Scene))
    {
        Scene->Tick(DeltaTime);
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

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    RootWidget->Draw();

    ImGui::ShowDemoWindow();
}

void REditor::DrawMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Test"))
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
}

void REditor::OnKeyUp(int Key, int Scancode, int Mode)
{
    Keys[Key] = GL_FALSE;
}

void REditor::OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition)
{
    MouseButtons[Button] = GL_TRUE;
    RootWidget->OnMouseDown(Button, Mods, CursorPosition);
}

void REditor::OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition)
{
    MouseButtons[Button] = GL_FALSE;
    RootWidget->OnMouseUp(Button, Mods, CursorPosition);
}

void REditor::OnMouseMove(const FVector2D& CursorPosition)
{
    if (MouseButtons[GLFW_MOUSE_BUTTON_RIGHT])
    {
        static FVector2D LastCursorPosition = CursorPosition;

        constexpr float Sensitivity = 0.05f;
        const FVector2D Delta = (CursorPosition - LastCursorPosition) * Sensitivity;
    
        ScreenCamera->setPitch(ScreenCamera->getPitch() - Delta.y);
        ScreenCamera->setYaw(ScreenCamera->getYaw() - Delta.x);
        LastCursorPosition = CursorPosition;
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

std::shared_ptr<RCamera> REditor::GetCamera() const
{
    return ScreenCamera;
}

std::pair<GLint, GLint> REditor::GetGLFWWindowSize(GLFWwindow* window)
{
    GLint width, height;
    glfwGetFramebufferSize(window, &width, &height);
    return std::make_pair(width, height);
}

void REditor::Move(GLdouble DeltaTime) const
{
    const GLfloat CameraSpeed = 5.0f * DeltaTime;
    if (Keys[GLFW_KEY_W])
    {
        ScreenCamera->setPosition(ScreenCamera->getPosition() + ScreenCamera->getFrontDirection() * CameraSpeed);
    }
    if (Keys[GLFW_KEY_S])
    {
        ScreenCamera->setPosition(ScreenCamera->getPosition() - ScreenCamera->getFrontDirection() * CameraSpeed);
    }
    if (Keys[GLFW_KEY_A])
    {
        ScreenCamera->setPosition(ScreenCamera->getPosition() - ScreenCamera->getRightDirection() * CameraSpeed);
    }
    if (Keys[GLFW_KEY_D])
    {
        ScreenCamera->setPosition(ScreenCamera->getPosition() + ScreenCamera->getRightDirection() * CameraSpeed);
    }
    
}

void REditor::Exit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void REditor::PreTick(GLdouble DeltaTime)
{
    Move(DeltaTime);
}
