#include "Renderer2D.hpp"

b2m2::Renderer2D::Renderer2D()
{
    m_handle = new cRenderer2D();
}

void b2m2::Renderer2D::Initalize(Matrix4 ^ projection)
{
    m_handle->Initalize(*projection->GetHandle());
}

void b2m2::Renderer2D::FillRectangle(Vector2 ^ pos, float width, float height, Color ^ color)
{
    m_handle->FillRectangle(*pos->GetHandle(), width, height, { color->R, color->G,color->B, color->A });
}

void b2m2::Renderer2D::DrawTexture(Texture2D ^ texture, Vector2 ^ pos)
{
    m_handle->DrawTexture(texture->GetHandle(), *pos->GetHandle());
}

void b2m2::Renderer2D::DrawTexture(Texture2D ^ texture, Vector2 ^ pos, Color ^ color)
{
    m_handle->DrawTexture(texture->GetHandle(), *pos->GetHandle(), { color->R,color->G,color->B,color->A });
}

void b2m2::Renderer2D::DrawTextureClip(Texture2D ^ texture, Vector2 ^ pos, Rectangle ^ clip)
{
    m_handle->DrawTextureClip(texture->GetHandle(), *pos->GetHandle(), { clip->X, clip->Y, clip->Width, clip->Height });
}

void b2m2::Renderer2D::DrawTextureClip(Texture2D ^ texture, Vector2 ^ pos, Rectangle ^ clip, Color ^ color)
{
    m_handle->DrawTextureClip(texture->GetHandle(), *pos->GetHandle(), { clip->X, clip->Y, clip->Width, clip->Height }, { color->R,color->G,color->B,color->A });
}

void b2m2::Renderer2D::DrawString(System::String ^ text, Font ^ font, Vector2^ pos, Color ^ color)
{
    const char * textcstr = (const char*)
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(text).ToPointer();
    m_handle->DrawString(textcstr, font->GetHandle(), *pos->GetHandle(), { color->R,color->G,color->B,color->A });
}

void b2m2::Renderer2D::Begin()
{
    m_handle->Begin();
}

void b2m2::Renderer2D::End()
{
    m_handle->End();
}

void b2m2::Renderer2D::Present()
{
    m_handle->Present();
}

void b2m2::Renderer2D::PushTransform(Matrix4 ^ matrix)
{
    m_handle->PushTransform(*matrix->GetHandle(), false);
}

void b2m2::Renderer2D::PushTransform(Matrix4 ^ matrix, bool override)
{
    m_handle->PushTransform(*matrix->GetHandle(), override);
}

void b2m2::Renderer2D::PopTransform()
{
    m_handle->PopTransform();
}
