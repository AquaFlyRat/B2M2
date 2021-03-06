#include "Renderer2D.hpp"

using namespace CharlieEngine;

Renderer2D::Renderer2D()
{
    m_handle = new arch::cRenderer2D();
}

void Renderer2D::Initalize(Matrix4 ^ projection)
{
    m_handle->Initalize(*projection->GetHandle());
}

void Renderer2D::FillRectangle(Vector2 ^ pos, float width, float height, Color ^ color)
{
    m_handle->FillRectangle(*pos->GetHandle(), width, height, { color->R, color->G,color->B, color->A });
}

void Renderer2D::DrawTexture(Texture2D ^ texture, Vector2 ^ pos)
{
    m_handle->DrawTexture(texture->GetHandle(), *pos->GetHandle());
}

void Renderer2D::DrawTexture(Texture2D ^ texture, Vector2 ^ pos, Color ^ color)
{
    m_handle->DrawTexture(texture->GetHandle(), *pos->GetHandle(), { color->R,color->G,color->B,color->A });
}

void Renderer2D::DrawTextureClip(Texture2D ^ texture, Vector2 ^ pos, Rectangle ^ clip)
{
    m_handle->DrawTextureClip(texture->GetHandle(), *pos->GetHandle(), { clip->X, clip->Y, clip->Width, clip->Height });
}

void Renderer2D::DrawTextureClip(Texture2D ^ texture, Vector2 ^ pos, Rectangle ^ clip, Color ^ color)
{
    m_handle->DrawTextureClip(texture->GetHandle(), *pos->GetHandle(), { clip->X, clip->Y, clip->Width, clip->Height }, { color->R,color->G,color->B,color->A });
}

void Renderer2D::DrawString(System::String ^ text, Font ^ font, Vector2^ pos, Color ^ color)
{
    const char * textcstr = (const char*)
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(text).ToPointer();
    m_handle->DrawString(textcstr, font->GetHandle(), *pos->GetHandle(), { color->R,color->G,color->B,color->A });
}

void CharlieEngine::Renderer2D::DrawString(System::String ^ text, Font ^ font, Vector2 ^ pos, Color ^ color, Vector2 ^ scale)
{
    const char * textcstr = (const char*)
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(text).ToPointer();
    m_handle->DrawString(textcstr, font->GetHandle(), *pos->GetHandle(), { color->R,color->G,color->B,color->A }, *scale->GetHandle());
}

void Renderer2D::DrawRectangle(Vector2 ^pos, float width, float height, Color ^ color)
{
    m_handle->DrawRectangle(*pos->GetHandle(), width, height, { color->R, color->G, color->B,color->A });
}

void CharlieEngine::Renderer2D::DrawRectangle(Vector2 ^ pos, float width, float height, Color ^ color, Vector2 ^ scale)
{
    m_handle->DrawRectangle(*pos->GetHandle(), width, height, { color->R, color->G, color->B,color->A }, *scale->GetHandle());
}

void CharlieEngine::Renderer2D::DrawRectangle(Vector2 ^ pos, float width, float height, Color ^ color, Vector2 ^ scale, float thickness)
{
    m_handle->DrawRectangle(*pos->GetHandle(), width, height, { color->R, color->G, color->B,color->A }, *scale->GetHandle(), thickness);
}

void CharlieEngine::Renderer2D::DrawLine(Vector2 ^ start, Vector2 ^ end, float thickness, Color^ color)
{
    m_handle->DrawLine(*start->GetHandle(), *end->GetHandle(), thickness, { color->R, color->G,color->B, color->A });
}

void Renderer2D::MoveCamera(Vector2 ^ offset)
{
    arch::cVector2 vec2 = *offset->GetHandle();
    m_handle->GetCamera()->Position.X += vec2.X;
    m_handle->GetCamera()->Position.Y += vec2.Y;
}

Vector2 ^ Renderer2D::GetCameraPosition()
{
    arch::cCamera *camera = m_handle->GetCamera();
    return gcnew Vector2(camera->Position.X, camera->Position.Y);
}

Vector2 ^ Renderer2D::UnProject(float viewWidth, float viewHeight, Vector2 ^ coords)
{
    arch::vec2 nat = m_handle->UnProject(viewWidth, viewHeight, *coords->GetHandle());
    return gcnew Vector2(nat.X, nat.Y);
}

void Renderer2D::SetProjection(Matrix4 ^ mat4)
{
    m_handle->SetProjection(*mat4->GetHandle());
}

void Renderer2D::Begin()
{
    m_handle->Begin();
}

void Renderer2D::End()
{
    m_handle->End();
}

void Renderer2D::Present()
{
    m_handle->Present();
}

void Renderer2D::PushTransform(Matrix4 ^ matrix)
{
    m_handle->PushTransform(*matrix->GetHandle(), false);
}

void Renderer2D::PushTransform(Matrix4 ^ matrix, bool override)
{
    m_handle->PushTransform(*matrix->GetHandle(), override);
}

void Renderer2D::PopTransform()
{
    m_handle->PopTransform();
}
