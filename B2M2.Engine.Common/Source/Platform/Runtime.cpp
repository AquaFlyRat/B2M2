/*
    @author Barney Wilks
*/

#include "Runtime.hpp"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "../Input/Keyboard.hpp"
#include "../Common.hpp"

void b2m2::cRuntime::Initalize() {
    int x = SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
}

void b2m2::cRuntime::Shutdown() {
    SDL_Quit();
    TTF_Quit();
}