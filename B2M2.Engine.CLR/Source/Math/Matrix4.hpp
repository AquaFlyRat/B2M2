#pragma once

#using <mscorlib.dll>

#include <Math/Matrix4.hpp>

#include "../ManagedClass.h"

#include "Vector3.hpp"
#include "Vector2.hpp"

namespace CharlieEngine {

    public ref class Matrix4 : ManagedClass<arch::cMatrix4> {
    private:
        Matrix4(arch::cMatrix4 *matrix);

    public:
        Matrix4(float diag);
        
        Matrix4 ^Multiply(Matrix4^ other);
        Vector3 ^Multiply(Vector3^ other);

        void Invert();

        static Matrix4^ Identity();
        static Matrix4^ Perpective(float aspectRatio, float foV, float far, float near);
        static Matrix4^ Orthographic(float right, float left, float top, float bottom, float far, float near);
        static Matrix4^ LookAt(const Vector3^ eyePosition, const Vector3^ lookAtPos, Vector3^ upVector);

        static Matrix4^ Translate(Vector3^ vec3);
        static Matrix4^ Translate(Vector2^ vector);

        static Matrix4^ Scale(Vector3^ vector);
        static Matrix4^ Scale(float factor);
        static Matrix4^ Scale(Vector2^ vector);

        static Matrix4^ RotateX(float theta);
        static Matrix4^ RotateY(float theta);
        static Matrix4^ RotateZ(float theta);

        float At(int x, int y) {
            return m_handle->Elements[x + y * 4];
        }

        void Set(float value, int x, int y) {
            m_handle->Elements[x + y * 4] = value;
        }
    };
};