/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"
#include <SDL2/SDL.h>

namespace b2m2 {
    struct sWindowConfig {
        uint32 Width;
        uint32 Height;

        const char * Title;
    };

    class cWindow {
    private:
        SDL_Window      *m_handle;
        SDL_GLContext   m_glContext;

        sWindowConfig    m_config;
        bool             m_bRunning = true;

        int32           m_glMajorVersion;
        int32           m_glMinorVersion;

    public:
        
        void Create(const sWindowConfig& config);
        void Destroy();
        void PollEvents();
        void SwapBuffers();

        SDL_Window *Handle() const { return m_handle; }
        bool        IsRunning() const { return m_bRunning; }

        uint32      GetGLMajorVersion() const { return m_glMajorVersion;  }
        uint32      GetGLMinorVersion() const { return m_glMinorVersion; }

    };
}