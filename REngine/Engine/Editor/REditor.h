#pragma once

#define GLEW_STATIC
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "Core/Public/Object/RObject.h"
#include "REngine/Engine/Runtime/EngineFramework/Math/Vector/FVector2D.h"
#include "ThirdParty/ExternalIncludes/GL/glew.h"
#include "ThirdParty/ExternalIncludes/GLFW/glfw3.h"

class RCameraComponent;
class RSubsystem;
struct FVector2D;
class REngineWindow;
class RMesh;
class RScene;
class RRootWindow;
class RWidget;
class RModel;
class RCameraLegacy;
class FShader;
class RFrame;

class REditor : public RObject
{
public:
    using RObject::RObject;
    
    void Initialize();
    void Exit();

    void PreTick(GLdouble DeltaTime);
    void Tick(GLdouble DeltaTime);

    void PreRender(GLdouble DeltaTime);
    void Render(GLdouble DeltaTime);
    void PostRender(GLdouble DeltaTime);

    void DrawUI(GLdouble DeltaTime);
    void DrawMainMenuBar();

    void OnKeyDown(int Key, int Scancode, int Mode);
    void OnKeyUp(int Key, int Scancode, int Mode);

    void OnMouseDown(int Button, int Mods, const FVector2D& CursorPosition);
    void OnMouseUp(int Button, int Mods, const FVector2D& CursorPosition);

    void OnMouseMove(const FVector2D& CursorPosition);

    static std::shared_ptr<REngineWindow> GetEngineWindow();
    std::shared_ptr<RFrame> GetFrame() const;
    static std::shared_ptr<RCameraComponent> GetCamera();

    template<std::derived_from<RSubsystem> T = RSubsystem>
    std::shared_ptr<T> GetSubsystem();

protected:
    static std::pair<GLint, GLint> GetGLFWWindowSize(GLFWwindow* window);
    
private:
    std::unordered_map<std::string, std::shared_ptr<RSubsystem>> Subsystems;
    std::shared_ptr<RFrame> Frame;
    std::shared_ptr<FShader> FrameShader;
    
    std::shared_ptr<RRootWindow> RootWidget;

    std::shared_ptr<RScene> Scene;

    GLboolean Keys[1024] = {};
    GLboolean MouseButtons[1024] = {};

    FVector2D LastCursorPosition;
};

#include "REdtior.tpp"
