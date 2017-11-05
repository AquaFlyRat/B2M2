/*
    @author Barney Wilks
*/

#pragma once

#include <math.h>

namespace b2m2 {
    class cVector3 {
    public:
        float X, Y, Z;

        cVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
        cVector3() : X(0), Y(0), Z(0) {}

        float Length() const {
            return sqrtf((X * X) + (Y * Y) + (Z * Z));
        }

        cVector3 operator-() const {
            return { -X, -Y, -Z };
        }

        static cVector3 Normalize(const cVector3& vec3) {
            float len = vec3.Length();

            return { vec3.X / len, vec3.Y / len, vec3.Z / len };
        }

        static float Dot(const cVector3& a, const cVector3& b) {
            float dot = a.X * b.X + a.Y * b.Y + a.Z * b.Z;
            return dot;
        }

        static cVector3 Cross(const cVector3& a, const cVector3& b) {
            float cx = (a.Y * b.Z) - (a.Z * b.Y);
            float cy = (a.Z * b.X) - (a.X * b.Z);
            float cz = (a.X * b.Y) - (a.Y * b.X);
            return { cx, cy, cz };
        }

        cVector3 operator+(const cVector3& b) {
            return { X + b.X, Y + b.Y, Z + b.Z };
        }

        cVector3 operator-(const cVector3& b) {
            return { X - b.X, Y - b.Y, Z - b.Z };
        }

        cVector3 operator*( const cVector3& b) {
            return { X * b.X, Y * b.Y, Z * b.Z };
        }
        
        cVector3 operator/(const cVector3& b) {
            return { X / b.X, Y / b.Y, Z / b.Z };
        }
    };
}
