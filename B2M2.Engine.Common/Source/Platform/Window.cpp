/*
    @author Barney Wilks
*/

#include "Window.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <Windows.h>

#include "../Graphics/Renderer2D.hpp"
#include "OpenGL.hpp"

using namespace arch;

void cWindow::Create(const sWindowConfig& config) {
    m_config = config;
    m_keyboardInputCallback = NULL;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    int winPosX = SDL_WINDOWPOS_UNDEFINED;
    int winPosY = SDL_WINDOWPOS_UNDEFINED;

    if (config.Flags & eWindowFlags::PositionCentre) {
        winPosX = winPosY = SDL_WINDOWPOS_CENTERED;
    }
    else if (config.Flags & eWindowFlags::PositionOrigin) {
        winPosX = winPosY = 0;
    }

    if (config.Flags & eWindowFlags::Borderless) {
        windowFlags |= SDL_WINDOW_BORDERLESS;
    }

    if (config.Flags & eWindowFlags::ShowOnCreate) {
        windowFlags |= SDL_WINDOW_SHOWN;
    }
    else {
        windowFlags |= SDL_WINDOW_HIDDEN;
    }

    m_handle = SDL_CreateWindow(
        config.Title, 
        winPosX, winPosY,
        config.Width, config.Height, 
        windowFlags
    );

    ASSERT(m_handle);
    
    m_glContext = SDL_GL_CreateContext(m_handle);

    ASSERT(m_glContext);

    glfl::set_function_loader(SDL_GL_GetProcAddress);
    glfl::load_everything();
    glViewport(0, 0, config.Width, config.Height);
    glGetIntegerv(GL_MAJOR_VERSION, &m_glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &m_glMinorVersion);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void cWindow::Show() {
    if (!(m_config.Flags & eWindowFlags::ShowOnCreate)) {
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

        if (e.type == SDL_WINDOWEVENT) {
            if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                int width = e.window.data1;
                int height = e.window.data2;
                glViewport(0, 0, width, height);
                /*cRenderer2D::GetShader()->Bind();
                cRenderer2D::GetShader()->SubmitUniformMat4("sys_Projection", cMatrix4::Orthographic(width, 0, 0, height, 1.f, -1.f));
                cRenderer2D::GetShader()->Unbind();*/
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