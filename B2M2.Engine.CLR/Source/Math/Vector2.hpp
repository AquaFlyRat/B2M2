#pragma once

#using <mscorlib.dll>
#include <Math/Vector2.hpp>

#include "../ManagedClass.h"

namespace b2m2 {

    public ref class Vector2 : ManagedClass<cVector2> {
    public:
        Vector2(float x, float y);
        Vector2();
        
        property float X {
            float get() { return m_handle->X; }
            void set(float x) { m_handle->X = x; }
        }

        property float Y {
            float get() { return m_handle->Y; }
            void set(float y) { m_handle->Y = y; }
        }
    };
};