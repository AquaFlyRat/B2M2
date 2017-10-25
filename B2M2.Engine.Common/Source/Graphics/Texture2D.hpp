/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"
#include <SDL2/SDL_image.h>

namespace b2m2 {
    class cTexture2D {
    public:
        enum eFiltering {
            Linear = GL_LINEAR, 
            Nearest = GL_NEAREST
        };

        void Create(const char *filepath, eFiltering format);
        void Release();

        uint32 GetWidth() const { return m_surface->w;  }
        uint32 GetHeight() const { return m_surface->h; }

        void Bind(uint32 slot);
        void UnBind(uint32 slot);

    private:
        void CreateGLTexture();
    
    private:
        GLuint m_id;
        eFiltering m_filtering;

        SDL_Surface *m_surface;
    };
}