#include <Platform/Window.hpp>
#include <Platform/Runtime.hpp>

#undef main

int main() {
    using namespace b2m2;

    cRuntime::Initalize();

    cWindow window;
    window.Create({ 800, 600, "B2M2 Engine!" });
    SDL_Delay(3000);
    window.Destroy();
    cRuntime::Shutdown();
    return 0;
}