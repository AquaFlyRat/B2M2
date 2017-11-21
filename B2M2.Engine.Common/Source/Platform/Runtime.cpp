/*
    @author Barney Wilks
*/

#include "Runtime.hpp"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../Graphics/Renderer2D.hpp"
#include "../Input/Keyboard.hpp"
#include "../Common.hpp"

void arch::cRuntime::Initalize() {
    int x = SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
}

void arch::cRuntime::Shutdown() {
    SDL_Quit();
    TTF_Quit();
}