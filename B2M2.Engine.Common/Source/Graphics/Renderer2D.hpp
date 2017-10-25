/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"

#include "OpenGL/OpenGLStructures.hpp"

#include "Shader.hpp"
#include "Texture2D.hpp"

#include <vector>

namespace b2m2 {
    struct sVertex
    {
        vec3        Position;
        vec4        Color;
        vec2        UV;
        float       TextureId;
    };

    class cRenderer2D {
    private:
        cVertexArray m_vao;
        cBuffer m_vbo, m_ibo;

        uint32 m_indices;
        sVertex *m_buffer;
        cShader *m_shader;
        std::vector<cTexture2D*> m_textures;

    public:
        void Initalize(cShader *shader, mat4 projectionMatrix);

        void FillRectangle(vec2 pos, float width, float height, vec4 color);
        void DrawTexture(cTexture2D *texture, vec2 pos);

        void Begin();
        void End();
        void Present();

    private:
        float GetTextureSlot(cTexture2D *texture);
    };
}