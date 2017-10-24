/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"
#include "Shader.hpp"

namespace b2m2 {
    struct cVertex
    {
        vec3        Position;
        vec4        Color;
        vec2        UV;
        float       TextureId;
    };

    class cRenderer2D {
    private:
        GLuint m_vao, m_vbo, m_ebo;
        uint32 m_indices;
        cVertex *m_buffer;
        cShader *m_shader;

    public:
        void Initalize(cShader *shader);

        void FillRectangle(vec2 pos, float width, float height, vec4 color);
        void Begin();
        void End();
        void Present();
    };
}