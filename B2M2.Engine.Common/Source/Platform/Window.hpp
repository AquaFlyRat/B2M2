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
        SDL_Window *m_handle;
        sWindowConfig m_config;

    public:
        void Create(const sWindowConfig& config);
        void Destroy();

        SDL_Window *Handle() const { return m_handle; }
    };
}