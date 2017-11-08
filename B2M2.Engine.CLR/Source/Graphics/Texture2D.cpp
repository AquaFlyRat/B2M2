#include "Texture2D.hpp"

b2m2::Texture2D::Texture2D(System::String^ filepath, TextureFiltering format)
{
    const char * title = (const char*)
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(filepath).ToPointer();

    m_handle = new cTexture2D;
    m_handle->Create(title, static_cast<cTexture2D::eFiltering>(format));
}

void b2m2::Texture2D::Destroy()
{
    m_handle->Release();
}
