/*
    @author Barney Wilks
*/

#pragma once

#include "Renderer2D.hpp"

using namespace b2m2;

static const int RenderableSize    = sizeof(cVertex) * 4;
static const int MaxRenderables    = 100;
static const int RendererBatchSize = RenderableSize * MaxRenderables;
static const int RendererIndexNum  = MaxRenderables * 6;

static void GenerateRectIndicesIntoBuffer(GLuint *buffer, int indicesNum)
{
    GLuint offset = 0;
    for (GLuint i = 0; i < indicesNum; i += 6)
    {
        buffer[i] = offset + 0;
        buffer[i + 1] = offset + 1;
        buffer[i + 2] = offset + 2;

        buffer[i + 3] = offset + 2;
        buffer[i + 4] = offset + 3;
        buffer[i + 5] = offset + 0;
        offset += 4;
    }
}

void cRenderer2D::Initalize(cShader *shader) {
    m_shader = shader;
    m_shader->Bind();

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, RendererBatchSize, NULL, GL_DYNAMIC_DRAW);

    GLuint *indices = new GLuint[RendererIndexNum];
    GenerateRectIndicesIntoBuffer(indices, RendererIndexNum);
    
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, RendererIndexNum, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cVertex), 0);    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(cVertex),
        (const GLvoid*) offsetof(cVertex, Color)
    );
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cVertex),
        (const GLvoid*)offsetof(cVertex, UV)
    );
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(cVertex), 
        (const GLvoid*)offsetof(cVertex, TextureId)
    );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    m_shader->Unbind();
    m_indices = 0;
}

void cRenderer2D::FillRectangle(vec2 pos, float width, float height, vec4 color) {
    m_indices += 6;
}

void cRenderer2D::Begin() {
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_buffer = reinterpret_cast<cVertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}

void cRenderer2D::End() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void cRenderer2D::Present() {
    m_shader->Bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glDrawElements(GL_TRIANGLES, m_indices, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    m_indices = 0;
    m_shader->Unbind();
}