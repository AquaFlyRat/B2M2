/*
    @author Barney Wilks
*/

#pragma once

#include "Renderer2D.hpp"
#include "Texture2D.hpp"
#include <SDL2/SDL_ttf.h>

using namespace b2m2;

static const int RenderableSize    = sizeof(sVertex) * 4;
static const int MaxRenderables    = 10000;
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

static vec3 MultiplyVec2ByMat4(float x, float y, const mat4& matrix) {
    vec4 vecOut = matrix * vec4(x, y, 0.f, 1.f);
    return vec3(vecOut.x, vecOut.y, 0.f);
}

void cRenderer2D::Initalize(cShader *shader, mat4 projectionMatrix) {
    m_shader = cShaderManager::CreateShaderFromFile("Shaders/vertex.shader", "Shaders/fragment.shader");
    m_transforms.push_back(mat4(1.0f));

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
    
    mat4 back = m_transforms.back();

    vec4 v = back * vec4(pos.x, pos.y, 0.f, 1.f);
    m_buffer->Position = MultiplyVec2ByMat4(pos.x, pos.y, back); //vec3(v.x, v.y, 0.f);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.x + width, pos.y, back);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.x + width, pos.y + height, back); 
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.x, pos.y + height, back);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;
    
    m_indices += 6;
}

void cRenderer2D::DrawTexture(cTexture2D * texture, vec2 pos)
{
    DrawTextureClip(texture, pos, sRectangle(0, 0, texture->GetWidth(), texture->GetHeight()));
}

void cRenderer2D::DrawTexture(cTexture2D * texture, vec2 pos, vec4 color)
{
    DrawTextureClip(texture, pos, sRectangle(0, 0, texture->GetWidth(), texture->GetHeight()), color);
}

void cRenderer2D::DrawTextureClip(cTexture2D * texture, vec2 pos, sRectangle clip)
{
    DrawTextureClip(texture, pos, clip, vec4(1.f, 1.f, 1.f, 1.f));
}

void cRenderer2D::DrawTextureClip(cTexture2D * texture, vec2 pos, sRectangle clip, vec4 color)
{
    float textureWidth = texture->GetWidth();
    float textureHeight = texture->GetHeight();

    float uvBoundX = clip.Size.x / textureWidth;
    float uvBoundY = clip.Size.y / textureHeight;

    float uvPosX = clip.Position.x / textureWidth;
    float uvPosY = clip.Position.y / textureHeight;

    float texSlot = GetTextureSlot(texture);

    float clipWidth = clip.Size.x;
    float clipHeight = clip.Size.y;

    mat4 back = m_transforms.back();

    m_buffer->Position = MultiplyVec2ByMat4(pos.x, pos.y, back);
    m_buffer->UV = vec2(uvPosX, uvPosY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.x + clipWidth, pos.y, back);
    m_buffer->UV = vec2(uvPosX + uvBoundX, uvPosY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.x + clipWidth, pos.y + clipHeight, back);
    m_buffer->UV = vec2(uvPosX + uvBoundX, uvPosY + uvBoundY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.x, pos.y + clipHeight, back);
    m_buffer->UV = vec2(uvPosX, uvPosY + uvBoundY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_indices += 6;
}

void cRenderer2D::DrawString(const std::string & text, cFont * font, vec2 pos, vec4 color)
{
    TTF_Font *sdlfont = font->GetTTF();
    const std::string& ascii = font->GetAsciiData();
    cTexture2D *texture = font->GetTexture();
    
    float xPos = pos.x;
    float yPos = pos.y;

    for (char c : text) {
        if (c == '\n' || c == '\r\n' || c == '\r') {
            yPos += texture->GetHeight();
            xPos = pos.x;
            continue;
        }

        float xoffset = 0.f;
        for (char _c = ascii[0]; _c != c; _c++) {
            int minx, maxx, miny, maxy, _advance;
            TTF_GlyphMetrics(sdlfont, _c, &minx, &maxx, &miny, &maxy, &_advance);
            xoffset += _advance;
        }
        
        int minx, maxx, miny, maxy, advance;
        TTF_GlyphMetrics(sdlfont, c, &minx, &maxx, &miny, &maxy, &advance);
        
        DrawTextureClip(texture, { xPos, yPos }, sRectangle(xoffset, 0, advance, texture->GetHeight()), color);

        xPos += advance;
    }
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
    m_transforms.clear();
    m_transforms.push_back(mat4(1.0f));
}

void cRenderer2D::PushTransform(const mat4 & matrix, bool override)
{
    if (override)
        m_transforms.push_back(matrix);
    else
        m_transforms.push_back(m_transforms.back() * matrix);
}

void cRenderer2D::PopTransform()
{
    if(m_transforms.size() > 1)
        m_transforms.pop_back();
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
