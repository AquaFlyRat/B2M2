/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"

namespace arch {
    struct sRectangle {
        vec2 Position;
        vec2 Size;

        sRectangle(float x, float y, float w, float h) : Position({ x, y }), Size({ w, h }) {}
    };
}