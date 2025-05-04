#include "REditor.h"

#include <string>


#include "Display/Frame/RFrame.h"
#include "Display/Shader/FShader.h"
#include "REngine/Engine/Runtime/GameFramework/Camera/RCamera.h"
#include "REngine/Engine/Runtime/GameFramework/Model/RModel.h"
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

void REditor::Init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    
    RootWidget = std::make_shared<RRootWindow>(GetSharedThis());
    RootWidget->Init(GetSharedThis<REditor>());

    const std::pair<GLint, GLint>& WindowSize = GetGLFWWindowSize(window);
    Frame = std::make_shared<RFrame>(WindowSize.first, WindowSize.second);
    
    FrameShader = std::make_shared<FShader>("Data/Shaders/frameShader.vs", "Data/Shaders/frameShader.frag");
    Shader = std::make_shared<FShader>("Data/Shaders/shader.vs", "Data/Shaders/shader.frag");

    ScreenCamera = std::make_shared<RCamera>(800, 600, 45.0f);
    ScreenCamera->setAngle({ 0.0f, -90.0f, 0.0f });

    MainModel = std::make_shared<RModel>("Content/objects/backpack/backpack.obj");
}

void REditor::Tick(GLdouble DeltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    
    PreRender(DeltaTime);

    ImGui::NewFrame();
    DrawMainMenuBar();
    DrawUI(DeltaTime);
    ImGui::EndFrame();

    ImGui::Render();
    Render(DeltaTime);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    PostRender(DeltaTime);
}

void REditor::PreRender(GLdouble DeltaTime)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void REditor::Render(GLdouble DeltaTime)
{
    Frame->Bind();

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader->Use();
    Shader->setUniform("pointLight.position", ScreenCamera->getPosition());
    Shader->setUniform("pointLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    Shader->setUniform("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    Shader->setUniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->setUniform("pointLight.constant", 1.0f);
    Shader->setUniform("pointLight.linear", 0.22f);
    Shader->setUniform("pointLight.constant", 0.20f);
    Shader->setUniform("viewPos", ScreenCamera->getPosition());

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

    Shader->setUniform("model", model);
    Shader->setUniform("view", ScreenCamera->getViewMatrix());
    Shader->setUniform("projection", ScreenCamera->getProjectionMatrix());

    MainModel->Draw(*Shader);
    
    Frame->Bind(0);
}

void REditor::PostRender(GLdouble DeltaTime)
{
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

void REditor::OnKeyDown(int key, int scancode, int mode)
{
    Keys[key] = GL_TRUE;
}

void REditor::OnKeyUp(int key, int scancode, int mode)
{
    Keys[key] = GL_FALSE;
}

void REditor::OnMouseDown(int button, int mods)
{
    
}

void REditor::OnMouseUp(int button, int mods)
{
    
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
