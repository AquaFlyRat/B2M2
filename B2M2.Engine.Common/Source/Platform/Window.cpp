/*
    @author Barney Wilks
*/

#include "Window.hpp"

using namespace b2m2;

void cWindow::Create(const sWindowConfig& config) {
    m_config = config;
    m_handle = SDL_CreateWindow(
        config.Title, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        config.Width, config.Height, 
        SDL_WINDOW_SHOWN
    );

    ASSERT(m_handle);
}

void cWindow::PollEvents() {
    static SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) m_bRunning = false;
    }
    SDL_UpdateWindowSurface(m_handle);
}

void cWindow::Destroy() {
    SDL_DestroyWindow(m_handle);
}