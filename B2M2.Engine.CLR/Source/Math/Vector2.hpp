#pragma once

#using <mscorlib.dll>
#include <glm/vec2.hpp>

#include "../ManagedClass.h"

namespace b2m2 {

    public ref class Vector2 : ManagedClass<glm::vec2> {
    public:
        Vector2(float x, float y);

        Vector2();
        
        property float X {
            float get() { return m_handle->x; }
            void set(float x) { m_handle->x = x; }
        }

        property float Y {
            float get() { return m_handle->y; }
            void set(float y) { m_handle->y = y; }
        }
    };
};