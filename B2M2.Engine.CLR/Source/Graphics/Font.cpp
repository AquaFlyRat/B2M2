#include "Font.hpp"

using namespace CharlieEngine;

Font::Font(System::String ^ font, int size)
{
    const char * title = (const char*)
        System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(font).ToPointer();

    m_handle = new arch::cFont;
    m_handle->Create(title, size);
}

void Font::Destroy()
{
    m_handle->Release();
}

Vector2 ^ Font::MeasureString(System::String ^ string)
{
    std::string outputstring;
    const char* kPtoC = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string)).ToPointer();
    outputstring = kPtoC;

    System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)kPtoC));

    arch::vec2 size = m_handle->MeasureString(outputstring);
    return gcnew Vector2(size.X, size.Y);
}
