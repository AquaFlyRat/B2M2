/*
    @author Barney Wilks
*/

#include "Window.hpp"

#include "OpenGL.hpp"

using namespace b2m2;

void cWindow::Create(const sWindowConfig& config) {
    m_config = config;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    m_handle = SDL_CreateWindow(
        config.Title, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        config.Width, config.Height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    ASSERT(m_handle);

    m_glContext = SDL_GL_CreateContext(m_handle);

    ASSERT(m_glContext);

    glfl::set_function_loader(SDL_GL_GetProcAddress);
    glfl::load_everything();

    glGetIntegerv(GL_MAJOR_VERSION, &m_glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &m_glMinorVersion);
}

void cWindow::PollEvents() {
    static SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) m_bRunning = false;
    }
}

void cWindow::SwapBuffers() {
    SDL_GL_SwapWindow(m_handle);
}

void cWindow::Destroy() {
    SDL_DestroyWindow(m_handle);
}