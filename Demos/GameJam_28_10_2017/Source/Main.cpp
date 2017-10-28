#include <B2M2.hpp>
#include "Player.hpp"

#undef main

int main()
{
    using namespace b2m2;
    cRuntime runtime;
    runtime.Initalize();

    cWindow window;
    window.Create({ 800, 600, "Game Jam" });
    window.SetClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    cRenderer2D renderer;
    renderer.Initalize(glm::ortho(0.f, 800.f, 600.f, 0.f, 1.f, -1.f));

    Player player;

    while (window.IsRunning()) {
        window.PollEvents();
        
        player.Tick();

        window.Clear();
   
        renderer.Begin();
        {
            renderer.PushTransform(glm::scale(vec3(4, 4, 0)));
            {
                player.Render(&renderer);
            }
            renderer.PopTransform();
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
