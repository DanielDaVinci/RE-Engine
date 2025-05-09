#pragma once

#define GLEW_STATIC
#include <memory>

#include "Core/Public/Object/RObject.h"
#include "ThirdParty/ExternalIncludes/GL/glew.h"
#include "ThirdParty/ExternalIncludes/GLFW/glfw3.h"

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
    
    void Initialize(GLFWwindow* window);
    void Exit();

    void PreTick(GLdouble DeltaTime);
    void Tick(GLdouble DeltaTime);

    void PreRender(GLdouble DeltaTime);
    void Render(GLdouble DeltaTime);
    void PostRender(GLdouble DeltaTime);

    void DrawUI(GLdouble DeltaTime);
    void DrawMainMenuBar();

    void OnKeyDown(int key, int scancode, int mode);
    void OnKeyUp(int key, int scancode, int mode);

    void OnMouseDown(int button, int mods);
    void OnMouseUp(int button, int mods);

    std::shared_ptr<RFrame> GetFrame() const;
    std::shared_ptr<RCamera> GetCamera() const;

protected:
    static std::pair<GLint, GLint> GetGLFWWindowSize(GLFWwindow* window);

    void Move(GLdouble DeltaTime) const;
    
private:
    std::shared_ptr<RFrame> Frame;
    std::shared_ptr<FShader> FrameShader;
    std::shared_ptr<FShader> Shader;
    std::shared_ptr<RCamera> ScreenCamera;

    std::shared_ptr<RModel> MainModel;
    std::shared_ptr<RRootWindow> RootWidget;

    std::shared_ptr<RScene> Scene;

    GLboolean Keys[1024] = {};
};
