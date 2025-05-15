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

    static std::shared_ptr<REngine> GetEngine();

    bool IsEngineActive() const;

    // ----------- Engine loop -----------
    void PreInitialize();
    void Initialize();
    void PostInitialize();

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
    static std::shared_ptr<REngine> SingletonEngine;
    bool bIsEngineActive;
    
    GLdouble DeltaTime;
    GLdouble CurrentTickTime;
    GLdouble PreviousTickTime;

    std::shared_ptr<REngineWindow> EngineWindow;
    std::shared_ptr<REditor> Editor;
};
