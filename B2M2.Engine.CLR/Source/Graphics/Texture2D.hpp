#pragma once

#using <mscorlib.dll>

#include <Graphics/Texture2D.hpp>

#include "../ManagedClass.h"

namespace CharlieEngine {
    public enum class TextureFiltering {
        Linear = arch::cTexture2D::eFiltering::Linear,
        Nearest = arch::cTexture2D::eFiltering::Nearest
    };

    public ref class Texture2D : ManagedClass<arch::cTexture2D> {
    public:
        Texture2D(System::String^ filepath, TextureFiltering format);

        property int Width {
            int get() { return m_handle->GetWidth(); }
        };

        property int Height {
            int get() { return m_handle->GetHeight(); }
        };

        void Destroy();
    };
};