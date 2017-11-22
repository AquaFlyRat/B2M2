#include <Platform/Window.hpp>
#include <Platform/Runtime.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Renderer2D.hpp>
#include <Graphics/Texture2D.hpp>
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
    using namespace arch;
    cRuntime runtime;

    cKeyboard::Initalize();
    runtime.Initalize();

    cWindow window;
    window.Create({ 800, 600, "arch Engine!", eWindowFlags::ShowOnCreate });
    window.SetClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    window.Show();
    cRenderer2D::InitShaders();

    cRenderer2D renderer;
    renderer.Initalize(cMatrix4::Orthographic(800, 0, 0, 600, 1.f, -1.f));
    uint32_t last_tick_time = 0;
    uint32_t delta = 0;
    while (window.IsRunning()) {
        window.PollEvents();
        
        window.Clear();
        uint32_t tick_time = SDL_GetTicks();
        delta = tick_time - last_tick_time;
        last_tick_time = tick_time;
        
        if (cKeyboard::IsKeyDown(SDL_SCANCODE_RIGHT)) {
            renderer.GetCamera()->Position.X += .0005f*delta;
        }

        if (cKeyboard::IsKeyDown(SDL_SCANCODE_LEFT)) {
            renderer.GetCamera()->Position.X -= .0005f*delta;
        }
        renderer.Begin();
        {
            renderer.DrawRectangle({ 100, 100 }, 100, 100, { 0.4f, 0.6f, 0.1f, 1.f });
        }
        renderer.End();
        renderer.Present();
        
        window.SwapBuffers();
        SDL_Delay(1000 / 60);
    }
    
    window.Destroy();   
    runtime.Shutdown();
    
    return 0;
}
