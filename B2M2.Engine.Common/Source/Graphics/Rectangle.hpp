/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"

namespace arch {
    struct sRectangle {
        vec2 Position;
        vec2 Size;

        sRectangle() : Position({ 0,0 }), Size({ 0,0 }) {}
        sRectangle(float x, float y, float w, float h) : Position({ x, y }), Size({ w, h }) {}
    };
}