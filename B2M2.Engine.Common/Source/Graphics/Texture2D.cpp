/*
    @author Barney Wilks
*/

#include "Texture2D.hpp"
#include "../Debug/Log.hpp"

using namespace b2m2;

void cTexture2D::Create(const char *filePath, eFiltering format){
    m_filtering = format;
    SDL_Surface *surface = IMG_Load(filePath);

    if (!surface) {
        B2M2_LOG(cLogger::eLevel::Fatal, "Cannot load texture file: " + std::string(filePath));
        ASSERT(false);
    }

    m_surface = surface;
    
    CreateGLTexture();
}

void cTexture2D::Create(SDL_Surface * surface, eFiltering filtering)
{
    m_filtering = filtering;
    m_surface = surface;
    CreateGLTexture();
}

void cTexture2D::CreateGLTexture() {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    GLenum filtering = static_cast<GLenum>(m_filtering);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_surface->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void cTexture2D::Bind(uint32 slot) {
    m_bIsBound = true;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void cTexture2D::UnBind(uint32 slot) {
    m_bIsBound = false;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void cTexture2D::Release() {
    SDL_FreeSurface(m_surface);
}