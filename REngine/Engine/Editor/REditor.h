#pragma once

#define GLEW_STATIC
#include <memory>

#include "Core/Public/Object/RObject.h"
#include "ThirdParty/ExternalIncludes/GL/glew.h"
#include "ThirdParty/ExternalIncludes/GLFW/glfw3.h"

struct FVector2D;
class REngineWindow;
class RMesh;
class RScene;
class RRootWindow;
class RWidget;
class RModel;
class RCamera;
class FShader;
class RFrame;

class REditor : public RObject
{
public:
    explicit REditor(const std::shared_ptr<RObject>& InOwner);
    ~REditor();
    
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
    std::shared_ptr<RCamera> GetCamera() const;

protected:
    static std::pair<GLint, GLint> GetGLFWWindowSize(GLFWwindow* window);

    void Move(GLdouble DeltaTime) const;
    
private:
    std::shared_ptr<RFrame> Frame;
    std::shared_ptr<FShader> FrameShader;
    std::shared_ptr<RCamera> ScreenCamera;
    
    std::shared_ptr<RRootWindow> RootWidget;

    std::shared_ptr<RScene> Scene;

    GLboolean Keys[1024] = {};
    GLboolean MouseButtons[1024] = {};
};
