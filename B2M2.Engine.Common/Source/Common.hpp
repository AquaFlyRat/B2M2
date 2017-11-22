/*
    @author Barney Wilks
*/

#pragma once

#include <assert.h>
#include <string>
#include <float.h>

#include "Math/Matrix4.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

#include "Platform/OpenGL.hpp"

namespace arch {
    typedef unsigned int  uint32;
    typedef int           int32;
    
    typedef unsigned char uint8;
    typedef char          int8;
    
    typedef cVector2 vec2;
    typedef cVector3 vec3;
    typedef cMatrix4 mat4;

    inline bool FloatsApproxEqual(float a1, float b1) {
        return( fabs(a1 - b1) <= FLT_EPSILON);
    }
}

#define ASSERT(x) assert(x)