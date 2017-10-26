/*
@author Barney Wilks
*/

#pragma once

#include "../Common.hpp"

namespace b2m2 {
    class cTransform {
    public:
        static mat4 RotateAroundPoint(const vec3& point, float angle);
    };
}