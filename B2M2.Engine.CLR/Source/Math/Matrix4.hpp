#pragma once

#using <mscorlib.dll>
#include <glm/matrix.hpp>

#include "../ManagedClass.h"

namespace b2m2 {

    public ref class Matrix4 : ManagedClass<glm::mat4> {
    public:
        Matrix4()
    };
};