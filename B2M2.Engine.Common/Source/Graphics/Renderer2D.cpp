/*
    @author Barney Wilks
*/

#pragma once

#include "Renderer2D.hpp"
#include "Texture2D.hpp"

using namespace b2m2;

static const int RenderableSize    = sizeof(sVertex) * 4;
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

void cRenderer2D::Initalize(cShader *shader, mat4 projectionMatrix) {
    m_shader = cShaderManager::CreateShaderFromFile("Shaders/vertex.shader", "Shaders/fragment.shader");

    m_shader->Bind();
    m_shader->SubmitUniformMat4("sys_Projection", projectionMatrix);
    int textureValues[] = { 0,1,2,3,4,5,6,7,8,9 };

    m_shader->SubmitUniform1iv("sys_Textures", 9, textureValues);

    m_vao.Generate();
    m_vao.Bind();

    m_vbo.Generate(GL_ARRAY_BUFFER, RendererBatchSize, NULL, GL_DYNAMIC_DRAW);
    m_vbo.Bind();

    size_t stride = sizeof(sVertex);

    m_vbo.AddAttribute({ 0, 3, GL_FLOAT, stride, offsetof(sVertex, Position) });
    m_vbo.AddAttribute({ 1, 4, GL_FLOAT, stride, offsetof(sVertex, Color) });
    m_vbo.AddAttribute({ 2, 2, GL_FLOAT, stride, offsetof(sVertex, UV) });
    m_vbo.AddAttribute({ 3, 1, GL_FLOAT, stride, offsetof(sVertex, TextureId) });

    GLuint *indices = new GLuint[RendererIndexNum];
    GenerateRectIndicesIntoBuffer(indices, RendererIndexNum);
    
    m_ibo.Generate(GL_ELEMENT_ARRAY_BUFFER, RendererIndexNum, indices, GL_STATIC_DRAW);
    m_ibo.Bind();

    m_shader->Unbind();
    m_indices = 0;
}

void cRenderer2D::FillRectangle(vec2 pos, float width, float height, vec4 color) {
    
    m_buffer->Position = vec3(pos.x, pos.y, 0.f);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = vec3(pos.x + width, pos.y, 0.f);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = vec3(pos.x + width, pos.y + height, 0.f);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = vec3(pos.x, pos.y + height, 0.f);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_indices += 6;
}

void cRenderer2D::DrawTexture(cTexture2D * texture, vec2 pos)
{
    float width = texture->GetWidth();
    float height = texture->GetHeight();

    float texSlot = GetTextureSlot(texture);

    m_buffer->Position = vec3(pos.x, pos.y, 0.f);
    m_buffer->UV = vec2(0, 0);
    m_buffer->TextureId = texSlot;
    m_buffer++;

    m_buffer->Position = vec3(pos.x + width, pos.y, 0.f);
    m_buffer->UV = vec2(1, 0);

    m_buffer->TextureId = texSlot;
    m_buffer++;

    m_buffer->Position = vec3(pos.x + width, pos.y + height, 0.f);
    m_buffer->UV = vec2(1, 1);
    m_buffer->TextureId = texSlot;
    m_buffer++;

    m_buffer->Position = vec3(pos.x, pos.y + height, 0.f);
    m_buffer->UV = vec2(0, 1);
    m_buffer->TextureId = texSlot;
    m_buffer++;

    m_indices += 6;
}

void cRenderer2D::Begin() {
    m_vao.Bind();
    m_buffer = m_vbo.Map<sVertex>();
}

void cRenderer2D::End() {
    m_vao.UnBind();
    m_vbo.ReleaseMapping();
}

void cRenderer2D::Present() {
    m_shader->Bind();

    for (int i = 0; i < m_textures.size(); i++)
        m_textures[i]->Bind(i);

    m_vao.Bind();
    m_ibo.Bind();
    
    glDrawElements(GL_TRIANGLES, m_indices, GL_UNSIGNED_INT, NULL);
    m_indices = 0;

    m_ibo.Bind();
    m_vao.UnBind();

    for (int i = 0; i < m_textures.size(); i++)
        m_textures[i]->UnBind(i);

    m_shader->Unbind();
}

float cRenderer2D::GetTextureSlot(cTexture2D * texture)
{
    for (int i = 0; i < m_textures.size(); i++) {
        if (m_textures[i] == texture) {
            return static_cast<float>(i);
        }
    }

    float size = static_cast<float>(m_textures.size());
    m_textures.push_back(texture);
    return size;
}
