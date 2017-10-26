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
        void(*m_keyboardInputCallback)(SDL_Event);

    public:
        
        void Create(const sWindowConfig& config);
        void Destroy();
        void PollEvents();
        void SwapBuffers();

        void SetClearColor(float r, float g, float b, float a);
        void Clear();

        void SetKeyDownCallback(void(*callback)(SDL_Event));

        SDL_Window *Handle() const { return m_handle; }
        bool        IsRunning() const { return m_bRunning; }

        uint32      GetGLMajorVersion() const { return m_glMajorVersion;  }
        uint32      GetGLMinorVersion() const { return m_glMinorVersion; }

    };
}