/*
    @author Barney Wilks
*/

#include "Spritesheet.hpp"

using namespace b2m2;

void cSpritesheet::Create(const char *spritesheetPath, float spriteWidth, float spriteHeight)
{
    m_texture = new cTexture2D;
    m_texture->Create(spritesheetPath, cTexture2D::eFiltering::Nearest);

    m_spriteWidth = spriteWidth;
    m_spriteHeight = spriteHeight;

    m_rows = m_texture->GetHeight() / m_spriteHeight;
    m_columns = m_texture->GetWidth() / m_spriteWidth;
}

void cSpritesheet::DrawSprite(cRenderer2D * renderer, int xIndex, int yIndex, vec2 pos)
{
    float rectX = xIndex * m_spriteWidth;
    float rectY = yIndex * m_spriteHeight;

    renderer->DrawTextureClip(m_texture, pos, sRectangle(rectX, rectY, m_spriteWidth, m_spriteHeight));
}

void cSpritesheet::AnimateRow(cRenderer2D * renderer, int row, vec2 pos, float period)
{
    static uint32 lastTime = SDL_GetTicks();
    static int spriteIndex = 0;

    uint32 currenttime = SDL_GetTicks();
    if (currenttime > lastTime + period) {
        spriteIndex++;
        if (spriteIndex >= m_columns) 
            spriteIndex = 0;
        lastTime = currenttime;
    }

    DrawSprite(renderer, spriteIndex, row, pos);
}

void cSpritesheet::Release()
{
    delete m_texture;
}
