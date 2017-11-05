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
    runtime.Initalize();
    cKeyboard::Initalize();
    
    cWindow window;
    window.Create({ 1280, 720, "B2M2 Engine!" });
    window.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    
    cRenderer2D renderer;
    renderer.Initalize(cMatrix4::Orthographic(1280, 0, 0, 720, 1.f, -1.f));

    cFont font;
    font.Create("Assets/WendyOne-Regular.ttf", 48);

    cSpritesheet playerSpritesheet;
    
    while (window.IsRunning()) {
        window.PollEvents();
        
        window.Clear();
        renderer.Begin();
        renderer.DrawString("Hello World!", &font, { 100, 100 }, { 0.f,1.f,1.f,1.f });
        renderer.End();
        renderer.Present();
        
        window.SwapBuffers();
        SDL_Delay(1000 / 60);
    }

    window.Destroy();
    
    runtime.Shutdown();

    return 0;
}
