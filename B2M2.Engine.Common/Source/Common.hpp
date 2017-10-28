/*
    @author Barney Wilks
*/

#pragma once

#include <assert.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <float.h>

#include "Platform/OpenGL.hpp"

namespace b2m2 {
    typedef unsigned int  uint32;
    typedef int           int32;
    
    typedef unsigned char uint8;
    typedef char          int8;

    typedef glm::vec2       vec2;
    typedef glm::tvec2<int> ivec2;
    
    typedef glm::vec3       vec3;
    typedef glm::tvec3<int> ivec3;

    typedef glm::vec4       vec4;
    typedef glm::tvec4<int> ivec4;
    typedef glm::mat4       mat4;

    inline bool ApproxEqual(float a1, float b1) {
        return( fabs(a1 - b1) <= FLT_EPSILON);
    }
}

#define ASSERT(x) assert(x)