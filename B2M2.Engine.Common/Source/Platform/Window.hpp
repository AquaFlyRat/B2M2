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
        sWindowConfig    m_config;
        bool             m_bRunning = true;

    public:
        
        void Create(const sWindowConfig& config);
        void Destroy();
        void PollEvents();

        SDL_Window *Handle() const { return m_handle; }
        bool        IsRunning() const { return m_bRunning; }
    };
}