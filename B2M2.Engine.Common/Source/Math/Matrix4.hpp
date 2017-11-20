#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"

#include <iostream>

namespace b2m2 {

    struct cVector4 {
        float X, Y, Z, W;
    };

    class cMatrix4
    {
    public:
        static constexpr int ElementCount = 16; // 4 x 4 matrix

    public:
        cMatrix4(float diag = 1.f);
        cMatrix4(float elements[ElementCount]);

        cMatrix4 Multiply(const cMatrix4& other);
        cVector3 Multiply(const cVector3& other);
        cVector4 Multiply(float x, float y, float z, float w);

        cMatrix4 operator*(const cMatrix4& other);
        cVector3 operator*(const cVector3& other);

        float Elements[ElementCount];

        void Invert();

        cVector3 ScreenToWorld(
            cMatrix4 projection,
            cMatrix4 view,
            const cVector2& screenPos,
            int viewWidth, int viewHeight
        );

        static cMatrix4 Identity(float diag = 1.f);
        static cMatrix4 Perpective(float aspectRatio, float foV, float far, float near);
        static cMatrix4 Orthographic(float right, float left, float top, float bottom, float far, float near);
        static cMatrix4 LookAt(const cVector3& eyePosition, const cVector3& lookAtPos, const cVector3& upVector);

        static cMatrix4 Translate(const cVector3& vec3);
        static cMatrix4 Translate(const cVector2& vector);
        static cMatrix4 Scale(const cVector3& vector);

        static cMatrix4 Scale(float factor);
        static cMatrix4 Scale(const cVector2& vector);
        
        static cMatrix4 RotateX(float theta);
        static cMatrix4 RotateY(float theta);
        static cMatrix4 RotateZ(float theta);

        static cVector2 TransformVector(const cVector2& vec, const cMatrix4& mat4);

        friend std::ostream& operator<<(std::ostream& os, const cMatrix4& matrix);
    };

    inline std::ostream& operator<<(std::ostream& os, const cMatrix4& matrix)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                os << matrix.Elements[j + i * 4] << ",";
            }
            os << std::endl;
        }
        return os;
    }
}