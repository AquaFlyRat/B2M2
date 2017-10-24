#pragma once

#include "Platform/Runtime.hpp"
#include "Platform/Window.hpp"
#undef main

int main(int argc, char* argv[])
{
    using namespace b2m2;

    cRuntime::Initalize();

    cWindow window;
    window.Create({ 800, 600, "B2M2 Engine" });

    SDL_Delay(3000);
    
    window.Destroy();
    cRuntime::Shutdown();

    return 0;
}