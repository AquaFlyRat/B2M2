/*
    @author Barney Wilks
*/

#pragma once

#include <math.h>

namespace arch {
    class cVector2 {
    public:
        float X, Y;

        cVector2(float x, float y): X(x), Y(y) {}
        cVector2() : X(0), Y(0) {}

        cVector2 operator+(const cVector2& b) {
            return { X + b.X, Y + b.Y };
        }

        cVector2 operator*(const cVector2& b) {
            return { X * b.X, Y * b.Y };
        }

        cVector2 operator*(const float& item) {
            return { X * item, Y * item };
        }

        cVector2 operator-(const cVector2& b) {
            return { X - b.X, Y - b.Y };
        }

        cVector2 operator/(const cVector2& b) {
            return { X / b.X, Y / b.Y };
        }

        float Length() const {
            return sqrtf((X * X) + (Y * Y));
        }

        static cVector2 Normalize(const cVector2& vec2) {
            float len = vec2.Length();

            return { vec2.X / len, vec2.Y / len };
        }
    };
}