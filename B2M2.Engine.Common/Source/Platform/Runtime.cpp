/*
    @author Barney Wilks
*/

#include "Runtime.hpp"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../Common.hpp"

void b2m2::cRuntime::Initalize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
}

void b2m2::cRuntime::Shutdown() {
    SDL_Quit();
    TTF_Quit();
}