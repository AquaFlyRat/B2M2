#pragma once

#include "../ManagedClass.h"

#include <Graphics/Font.hpp>
#include "../Math/Vector2.hpp"

namespace b2m2 {
    public ref class Font : ManagedClass<cFont> {
    public:
        Font(System::String^ font, int size);
        void Destroy();

        Vector2 ^MeasureString(System::String^ string);
    };
}