/*
    @author Barney Wilks
*/

#include "Font.hpp"

using namespace b2m2;

void cFont::Create(const char * font, float size)
{
    m_sdlFont = TTF_OpenFont(font, size);
    std::string t;
    for (char c = 32; c <= 126; c++) t += c;
    m_ascii = t;
    SDL_Surface *surface = TTF_RenderText_Blended(m_sdlFont, t.c_str(), { 255,255,255,255 });
    m_texture = new cTexture2D;
    m_texture->Create(surface, cTexture2D::eFiltering::Linear);
}

void cFont::Release()
{
    delete m_texture;
    TTF_CloseFont(m_sdlFont);
}

vec2 cFont::MeasureString(const std::string & text)
{
    int w, h;
    TTF_SizeText(m_sdlFont, text.c_str(), &w, &h);
    return { w, h };
}
