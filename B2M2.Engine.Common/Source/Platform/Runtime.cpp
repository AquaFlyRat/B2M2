#include "Runtime.hpp"

#include <SDL2/SDL.h>

void b2m2::cRuntime::Initalize() {
    SDL_Init(SDL_INIT_EVERYTHING);
}

void b2m2::cRuntime::Shutdown() {
    SDL_Quit();
}