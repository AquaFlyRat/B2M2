/*
    @author Barney Wilks
*/

#pragma once

#include <SDL2/SDL_ttf.h>
#include "Texture2D.hpp"

namespace b2m2 {
    class cFont {
    public:
        void Create(const char *font, float size);
        void Release();

        TTF_Font *GetTTF() const { return m_sdlFont; }
        cTexture2D* GetTexture() const { return m_texture; }
        const std::string& GetAsciiData() const { return m_ascii; }

        vec2 MeasureString(const std::string& text);
    private:
        float m_size;
        TTF_Font *m_sdlFont;
        cTexture2D *m_texture;
        std::string m_ascii;
    };
}