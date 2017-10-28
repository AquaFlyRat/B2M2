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
        int m_animationIndex;

    public:
        cSpritesheet();
        
        void Create(const char *spritesheetPath, float spriteWidth, float spriteHeight);

        void DrawSprite(cRenderer2D *renderer, int xIndex, int yIndex, vec2 pos, vec2 scale = {1, 1});
        void AnimateRow(cRenderer2D *renderer, int row, vec2 pos, float period, int cap = -1, vec2 scale = { 1, 1 });
        void ResetAnimations();

        void Release();
    };
}
