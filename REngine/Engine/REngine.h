#pragma once
#include <memory>

#define GLEW_STATIC
#include "Core/Public/Object/RObject.h"
#include "ThirdParty/ExternalIncludes/GL/glew.h"
#include "ThirdParty/ExternalIncludes/GLFW/glfw3.h"

class REditor;
class REngineWindow;

class REngine : public RObject
{
    using ThisClass = REngine;
public:
    explicit REngine(const std::shared_ptr<RObject>& InOwner);
    ~REngine();

    bool IsEngineActive() const;

    // ----------- Engine loop -----------
    void PreInit();
    void Init();
    void PostInit();

    void PreTick();
    void Tick();
    void PostTick();

    void Exit();
    // ---------------------------------

    std::shared_ptr<REditor> GetEditor() const;

protected:
    // ----------- Callbacks -----------
    class FCallbackWrapper
    {
    public:
        static REngine* StaticEngine;
        
        FCallbackWrapper() = delete;
        FCallbackWrapper(const FCallbackWrapper&) = delete;
        FCallbackWrapper(FCallbackWrapper&&) = delete;
        ~FCallbackWrapper() = delete;

        static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    };

    void SetWindowCallbacks();
    void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) const;
    void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) const;
    // ---------------------------------
    
private:
    bool bIsEngineActive;
    
    GLdouble DeltaTime;
    GLdouble CurrentTickTime;
    GLdouble PreviousTickTime;

    std::shared_ptr<REngineWindow> EngineWindow;
    std::shared_ptr<REditor> Editor;
};

static std::shared_ptr<REngine> Engine = nullptr;
