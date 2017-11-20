/*
    @author Barney Wilks
*/

#pragma once

#include "Renderer2D.hpp"
#include "Texture2D.hpp"
#include "../Debug/Log.hpp"
#include <limits>
#include <SDL2/SDL_ttf.h>

#include "OpenGL/Shaders/Renderer2DShader.h"

using namespace b2m2;

static const int RenderableSize    = sizeof(sVertex) * 4;
static const int MaxRenderables    = 10000;
static const int RendererBatchSize = RenderableSize * MaxRenderables;
static const int RendererIndexNum  = MaxRenderables * 6;

cMatrix4 cCamera::GetMatrix() {
    cVector2 inversePos(-Position.X, -Position.Y);
    cMatrix4 transform = cMatrix4::Translate(inversePos);
    return transform;
}

static void GenerateRectIndicesIntoBuffer(GLuint *buffer, uint32 indicesNum) {
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

static vec3 MultiplyVec2ByMat4(float x, float y, const cMatrix4& matrix) {
    cVector3 _vec3(x, y, 0.f);
    cMatrix4 cpy = matrix;
    cVector3 vecOut = cpy * _vec3;

    return vec3(vecOut.X, vecOut.Y, 0.f);
}

cShader *cRenderer2D::GetShader() {
    return s_2dshader;
}

void cRenderer2D::Initalize(mat4 projectionMatrix) {
    m_projection = projectionMatrix;
    
    m_transforms.push_back(mat4(1.0f));
    m_quadCount = 0;

    s_2dshader->Bind();
    s_2dshader->SubmitUniformMat4("sys_Projection", projectionMatrix);

    int textureValues[] = { 0,1,2,3,4,5,6,7,8,9 };

    s_2dshader->SubmitUniform1iv("sys_Textures", 9, textureValues);

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

    s_2dshader->Unbind();
    m_indices = 0;
}

void cRenderer2D::FillRectangle(vec2 pos, float width, float height, cColor color) {
    
    mat4 back = m_transforms.back();

    vec3 v = back * cVector3(pos.X, pos.Y, 0.f);
    m_buffer->Position = MultiplyVec2ByMat4(pos.X, pos.Y, back);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.X + width, pos.Y, back);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.X + width, pos.Y + height, back); 
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.X, pos.Y + height, back);
    m_buffer->Color = color;
    m_buffer->TextureId = -1;
    m_buffer++;
    
    m_indices += 6;
    m_tmpQuadCount++;
}

void cRenderer2D::DrawTexture(cTexture2D * texture, vec2 pos) {
    DrawTextureClip(texture, pos, sRectangle(0, 0, static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight())));
}

void cRenderer2D::DrawTexture(cTexture2D * texture, vec2 pos, cColor color) {
    DrawTextureClip(texture, pos, sRectangle(0, 0, static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight())), color);
}

void cRenderer2D::DrawTextureClip(cTexture2D * texture, vec2 pos, sRectangle clip, vec2 scale) {
    DrawTextureClip(texture, pos, clip, { 255, 255, 255,255 }, scale);
}

void cRenderer2D::DrawTextureClip(cTexture2D * texture, vec2 pos, sRectangle clip, cColor color, vec2 scale) {
    uint32 textureWidth = texture->GetWidth();
    uint32 textureHeight = texture->GetHeight();

    float uvBoundX = clip.Size.X / textureWidth;
    float uvBoundY = clip.Size.Y / textureHeight;

    float uvPosX = clip.Position.X / textureWidth;
    float uvPosY = clip.Position.Y / textureHeight;

    float texSlot = GetTextureSlot(texture);

    float clipWidth = clip.Size.X * scale.X;
    float clipHeight = clip.Size.Y * scale.Y;

    mat4 back = m_transforms.back();

    m_buffer->Position = MultiplyVec2ByMat4(pos.X, pos.Y, back);
    m_buffer->UV = vec2(uvPosX, uvPosY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.X + clipWidth, pos.Y, back);
    m_buffer->UV = vec2(uvPosX + uvBoundX, uvPosY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.X + clipWidth, pos.Y + clipHeight, back);
    m_buffer->UV = vec2(uvPosX + uvBoundX, uvPosY + uvBoundY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(pos.X, pos.Y + clipHeight, back);
    m_buffer->UV = vec2(uvPosX, uvPosY + uvBoundY);
    m_buffer->TextureId = texSlot;
    m_buffer->Color = color;
    m_buffer++;

    m_indices += 6;
    
    m_tmpQuadCount++;
}

void cRenderer2D::DrawString(const std::string & text, cFont * font, vec2 pos, cColor color) {
    TTF_Font *sdlfont = font->GetTTF();
    const std::string& ascii = font->GetAsciiData();
    cTexture2D *texture = font->GetTexture();
    
    float xPos = pos.X;
    float yPos = pos.Y;

    for (char c : text) {
        if (c == '\n') {
            yPos += texture->GetHeight();
            xPos = pos.X;
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
        
        DrawTextureClip(texture, { xPos, yPos }, sRectangle(xoffset, 0, static_cast<float>(advance), static_cast<float>(texture->GetHeight())), color);

        xPos += advance;
    }
}

void cRenderer2D::DrawLine(const cVector2 & start, const cVector2 & end, float thickness, cColor color) {
    mat4 back = m_transforms.back();

    cVector2 normal = cVector2::Normalize(vec2(end.Y - start.Y, -(end.X - start.X))) * thickness;

    m_buffer->Position = MultiplyVec2ByMat4(start.X + normal.X, start.Y + normal.Y, back);
    m_buffer->TextureId = -1;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(end.X + normal.X, end.Y + normal.Y, back);
    m_buffer->TextureId = -1;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(end.X - normal.X, end.Y - normal.Y, back);
    m_buffer->TextureId = -1;
    m_buffer->Color = color;
    m_buffer++;

    m_buffer->Position = MultiplyVec2ByMat4(start.X - normal.X, start.Y - normal.Y, back);
    m_buffer->TextureId = -1;
    m_buffer->Color = color;
    m_buffer++;

    m_indices += 6;
}

void cRenderer2D::DrawRectangle(const cVector2 & pos, float width, float height, cColor color) {
    const float thickness = 2.f;

    DrawLine({ pos.X, pos.Y }, { pos.X + width, pos.Y }, thickness, color);
    DrawLine({ pos.X + width, pos.Y }, { pos.X + width, pos.Y + height }, thickness, color);
    DrawLine({ pos.X + width, pos.Y + height }, { pos.X, pos.Y + height }, thickness, color);
    DrawLine({ pos.X, pos.Y + height }, { pos.X, pos.Y }, thickness, color);
}

void cRenderer2D::SetProjection(cMatrix4 mat4)
{
    m_projection = mat4;
    s_2dshader->Bind();
    s_2dshader->SubmitUniformMat4("sys_Projection", mat4);
    s_2dshader->Unbind();
}

void cRenderer2D::Begin() {
    m_vao.Bind();
    m_buffer = m_vbo.Map<sVertex>();
}

void cRenderer2D::End() {
    m_quadCount = m_tmpQuadCount;
    m_tmpQuadCount = 0;

    m_vao.UnBind();
    m_vbo.ReleaseMapping();
}

void cRenderer2D::Present() {
    s_2dshader->Bind();
    s_2dshader->SubmitUniformMat4("sys_View", m_camera.GetMatrix());
    for (size_t i = 0; i < m_textures.size(); i++)
        m_textures[i]->Bind(i);

    m_vao.Bind();
    m_ibo.Bind();
    
    glDrawElements(GL_TRIANGLES, m_indices, GL_UNSIGNED_INT, NULL);
    m_indices = 0;

    m_ibo.Bind();
    m_vao.UnBind();

    for (size_t i = 0; i < m_textures.size(); i++)
        m_textures[i]->UnBind(i);

    s_2dshader->Unbind();
    m_transforms.clear();
    m_transforms.push_back(mat4(1.0f));
}

cVector2 cRenderer2D::UnProject(float viewWidth, float viewHeight, const cVector2 & coords)
{
    // TODO: This should be a proper Screen -> World matrix conversion thingy. This is very dependant on a 1:1 pixel GL projection mapping.
    return m_camera.Position + coords;
}

void cRenderer2D::PushTransform(const mat4 & matrix, bool override) {
    if (override)
        m_transforms.push_back(matrix);
    else {
        mat4 back = m_transforms.back();
        m_transforms.push_back(back * matrix);
    }
}

void cRenderer2D::PopTransform() {
    if(m_transforms.size() >= 1)
        m_transforms.pop_back();
}

cShader *cRenderer2D::s_2dshader = NULL;

void cRenderer2D::InitShaders()
{
    s_2dshader = cShaderManager::CreateShaderFromText(Renderer2DShaderText::Vertex.c_str(), Renderer2DShaderText::Fragment.c_str());
}

float cRenderer2D::GetTextureSlot(cTexture2D * texture) {
    for (size_t i = 0; i < m_textures.size(); i++) {
        if (m_textures[i] == texture) {
            return static_cast<float>(i);
        }
    }
    
    if (m_textures.size() == 32) {
        B2M2_LOG(cLogger::eLevel::Warning, "Already drawing 32 texture units with buffer. Flushing renderer now.");
    }

    float size = static_cast<float>(m_textures.size());
    m_textures.push_back(texture);
    return size;
}
