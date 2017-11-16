#include <Platform/Window.hpp>
#include <Platform/Runtime.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer2D.hpp>
#include <Graphics/Texture2D.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Graphics/Transform.hpp>
#include <Input/Keyboard.hpp>
#include <Windows.h>
#include <Runtime/Animation/Spritesheet.hpp>
#include <Box2D/Box2D.h>
#include <Runtime/Scene/Scene.hpp>
#include <Runtime/CoreComponents/PhysicsComponent.hpp>

#undef main

int main()
{
    using namespace b2m2;
    cRuntime runtime;

    cKeyboard::Initalize();
    runtime.Initalize();

    cWindow window;
    window.Create({ 800, 600, "B2M2 Engine!", eWindowFlags::ShowOnCreate });
    window.SetClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    window.Show();
    cRenderer2D::InitShaders();

    cRenderer2D renderer;
    renderer.Initalize(cMatrix4::Orthographic(800, 0, 0, 600, 1.f, -1.f));
    while (window.IsRunning()) {
        window.PollEvents();
        
        window.Clear();
        renderer.Begin();
        {
            renderer.DrawRectangle({ 100, 100 }, 100, 100, { 0.4f, 0.6f, 0.1f, 1.f });
        }
        renderer.End();
        renderer.Present();
        
        window.SwapBuffers();
    }
    
    window.Destroy();   
    runtime.Shutdown();
    
    return 0;
}
