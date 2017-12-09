/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"

#include "OpenGL/OpenGLStructures.hpp"

#include "Shader.hpp"
#include "Texture2D.hpp"
#include "Rectangle.hpp"
#include "Font.hpp"
#include "Color.hpp"

#include <vector>

namespace arch {
    struct sVertex {
        vec3        Position;
        cColor      Color;
        vec2        UV;
        float       TextureId;
    };

    class cCamera {
    public:
        vec2        Position;
        
        cMatrix4 GetMatrix();
    };

    class cRenderer2D {
    private:
        cVertexArray             m_vao;
        cBuffer                  m_vbo, m_ibo;
        cMatrix4                 m_projection;
        uint32                   m_indices;
        sVertex                 *m_buffer;
        cShader                 *m_shader;
        std::vector<cTexture2D*> m_textures;
        std::vector<mat4>        m_transforms;
        uint32                   m_quadCount;
        uint32                   m_tmpQuadCount = 0;
        cCamera                  m_camera;

    public:
        void            Initalize(mat4 projectionMatrix);

        void            FillRectangle(vec2 pos, float width, float height, cColor color);
        void            DrawTexture(cTexture2D *texture, vec2 pos);
        void            DrawTexture(cTexture2D *texture, vec2 pos, cColor color);

        void            DrawTextureClip(cTexture2D *texture, vec2 pos, sRectangle clip, vec2 scale = { 1.f, 1.f });
        void            DrawTextureClip(cTexture2D *texture, vec2 pos, sRectangle clip, cColor color, vec2 scale = { 1.f, 1.f });

        void            DrawString(const std::string& text, cFont *font, vec2 pos, cColor color, cVector2 scale = { 1.f, 1.f });
        
        void            DrawLine(const cVector2& start, const cVector2& end, float thickness, cColor color);
        void            DrawRectangle(const cVector2& pos, float width, float height, cColor color, cVector2 scale = { 1.f, 1.f });

        void            SetProjection(cMatrix4 mat4);

        void            Begin();
        void            End();
        void            Present();

        cVector2        UnProject(float viewWidth, float viewHeight, const cVector2& coords);

        void            PushTransform(const mat4& matrix, bool override = false);
        void            PopTransform();

        inline cCamera *GetCamera() { return &m_camera; }
        inline uint32   GetQuadCount() const { return m_quadCount; }

        static cShader *GetShader();
        static void     InitShaders();

    private:
        float GetTextureSlot(cTexture2D *texture);
        
        static cShader *s_2dshader;
    };
}