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
    cKeyboard::Initalize();
    
    cWindow window;
    cRuntime runtime;
    runtime.Initalize();
    window.Create({ 800, 600, "B2M2 Engine!" });
    window.SetClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    
    cRenderer2D renderer;
    renderer.Initalize(cMatrix4::Orthographic(800, 0, 0, 600, 1.f, -1.f));
    /*
    cFont font;
    font.Create("Assets/WendyOne-Regular.ttf", 48);

    cSpritesheet playerSpritesheet;
    */
    while (window.IsRunning()) {
        window.PollEvents();
        
        window.Clear();
        renderer.Begin();
        renderer.FillRectangle({ 100,100 }, 100, 100, { 1.0f, 0.0f, 0.0f, 1.0f });

        renderer.End();
        renderer.Present();
        
        window.SwapBuffers();
    }
    /*
    window.Destroy();
    
    runtime.Shutdown();
    */
    return 0;
}
