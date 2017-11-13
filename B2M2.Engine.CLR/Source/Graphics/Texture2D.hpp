#pragma once

#using <mscorlib.dll>

#include <Graphics/Texture2D.hpp>

#include "../ManagedClass.h"

namespace CharlieEngine {
    public enum class TextureFiltering {
        Linear = b2m2::cTexture2D::eFiltering::Linear,
        Nearest = b2m2::cTexture2D::eFiltering::Nearest
    };

    public ref class Texture2D : ManagedClass<b2m2::cTexture2D> {
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