/*
    @author Barney Wilks
*/

#include "Spritesheet.hpp"

using namespace b2m2;

cSpritesheet::cSpritesheet(): m_animationIndex(0)
{
}

void cSpritesheet::Create(const char *spritesheetPath, float spriteWidth, float spriteHeight)
{
    m_texture = new cTexture2D;
    m_texture->Create(spritesheetPath, cTexture2D::eFiltering::Nearest);

    m_spriteWidth = spriteWidth;
    m_spriteHeight = spriteHeight;

    m_rows = m_texture->GetHeight() / m_spriteHeight;
    m_columns = m_texture->GetWidth() / m_spriteWidth;
}

void cSpritesheet::DrawSprite(cRenderer2D * renderer, int xIndex, int yIndex, vec2 pos, vec2 scale)
{
    float rectX = xIndex * m_spriteWidth;
    float rectY = yIndex * m_spriteHeight;

    renderer->DrawTextureClip(m_texture, pos, sRectangle(rectX, rectY, m_spriteWidth, m_spriteHeight), scale);
}

void cSpritesheet::AnimateRow(cRenderer2D * renderer, int row, vec2 pos, float period, int cap, vec2 scale)
{
    cap = cap < 0 ? m_columns : cap;

    static uint32 lastTime = SDL_GetTicks();
    
    uint32 currenttime = SDL_GetTicks();
    if (currenttime > lastTime + period) {
        m_animationIndex++;
        if (m_animationIndex >= cap)
            m_animationIndex = 0;
        lastTime = currenttime;
    }

    DrawSprite(renderer, m_animationIndex, row, pos, scale);
}

void cSpritesheet::ResetAnimations()
{
    m_animationIndex = 0;
}

void cSpritesheet::Release()
{
    delete m_texture;
}
