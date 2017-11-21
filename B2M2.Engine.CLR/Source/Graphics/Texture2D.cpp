#include "Texture2D.hpp"

using namespace CharlieEngine;

Texture2D::Texture2D(System::String^ filepath, TextureFiltering format)
{
    const char * title = (const char*)
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(filepath).ToPointer();

    m_handle = new arch::cTexture2D;
    m_handle->Create(title, static_cast<arch::cTexture2D::eFiltering>(format));
}

void Texture2D::Destroy()
{
    m_handle->Release();
}
