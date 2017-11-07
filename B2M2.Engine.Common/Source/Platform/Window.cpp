/*
    @author Barney Wilks
*/

#include "Window.hpp"

#include "OpenGL.hpp"

using namespace b2m2;

void cWindow::Create(const sWindowConfig& config) {
    m_config = config;
    m_keyboardInputCallback = NULL;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    Uint32 windowFlags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL;
    /*if (config.ShowOnCreate) {
        windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    }*/

    m_handle = SDL_CreateWindow(
        config.Title, 
        0, 0, 
        config.Width, config.Height, 
        windowFlags
    );

    ASSERT(m_handle);
    
    m_glContext = SDL_GL_CreateContext(m_handle);

    ASSERT(m_glContext);

    glfl::set_function_loader(SDL_GL_GetProcAddress);
    glfl::load_everything();

    glGetIntegerv(GL_MAJOR_VERSION, &m_glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &m_glMinorVersion);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void cWindow::Show() {
    if (!m_config.ShowOnCreate) {
        SDL_ShowWindow(m_handle);
    }
}

void cWindow::PollEvents() {
    static SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) 
            m_bRunning = false;
        if (e.type == SDL_KEYDOWN) {
            if (m_keyboardInputCallback) {
                m_keyboardInputCallback(e);
            }
        }
    }
}

void cWindow::SwapBuffers() {
    SDL_GL_SwapWindow(m_handle);
}

void cWindow::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void cWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cWindow::SetKeyDownCallback(void(*callback)(SDL_Event))
{
    m_keyboardInputCallback = callback;
}

void cWindow::Destroy() {
    SDL_DestroyWindow(m_handle);
}