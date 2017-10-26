/*
    @author Barney Wilks
*/

#pragma once

#include "../../Graphics/Texture2D.hpp"
#include "../../Graphics/Renderer2D.hpp"

namespace b2m2 {
    class cSpritesheet {
    private:
        float m_spriteWidth, m_spriteHeight;
        cTexture2D *m_texture;
        int m_rows, m_columns;

    public:
        void Create(const char *spritesheetPath, float spriteWidth, float spriteHeight);

        void DrawSprite(cRenderer2D *renderer, int xIndex, int yIndex, vec2 pos);
        void AnimateRow(cRenderer2D *renderer, int row, vec2 pos, float period);

        void Release();
    };
}
