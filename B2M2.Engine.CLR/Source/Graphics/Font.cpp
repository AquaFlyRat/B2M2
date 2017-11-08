#include "Font.hpp"

b2m2::Font::Font(System::String ^ font, int size)
{
    const char * title = (const char*)
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(font).ToPointer();

    m_handle = new cFont;
    m_handle->Create(title, size);
}

void b2m2::Font::Destroy()
{
    m_handle->Release();
}

b2m2::Vector2 ^ b2m2::Font::MeasureString(System::String ^ string)
{
    std::string outputstring;
    const char* kPtoC = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string)).ToPointer();
    outputstring = kPtoC;

    System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)kPtoC));

    vec2 size = m_handle->MeasureString(outputstring);
    return gcnew Vector2(size.X, size.Y);
}
