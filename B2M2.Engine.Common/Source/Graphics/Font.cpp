/*
    @author Barney Wilks
*/

#include "Font.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "../Containers/String.hpp"

using namespace b2m2;

void cFont::Create(const char* font, int32 size)
{
    m_sdlFont = TTF_OpenFont(font, size);
    std::string ascii;
    
    for (char c = 32; c <= 126; c++) {
        ascii += c;
    }

    m_ascii = ascii;

    SDL_Surface *surface = TTF_RenderText_Blended(m_sdlFont, ascii.c_str(), { 255,255,255,255 });
    
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
    std::vector<std::string> strs = SplitString(text, '\n');

    float width = 0.f;
    float height = 0.f;

    for (const std::string& str : strs) {
        int w, h;
        TTF_SizeText(m_sdlFont, str.c_str(), &w, &h);
        
        if (w > width) {
            width = static_cast<float>(w); 
        }

        height += (float)h;
    }

    return { width, height };
}
