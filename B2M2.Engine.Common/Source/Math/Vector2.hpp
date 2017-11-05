/*
    @author Barney Wilks
*/

#pragma once

namespace b2m2 {
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

        cVector2 operator-(const cVector2& b) {
            return { X - b.X, Y - b.Y };
        }

        cVector2 operator/(const cVector2& b) {
            return { X / b.X, Y / b.Y };
        }
    };
}