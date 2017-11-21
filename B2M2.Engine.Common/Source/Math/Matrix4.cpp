#include "Matrix4.hpp"
#include "Maths.hpp"

#include <string.h>
#include <math.h>
#include <assert.h>

using namespace arch;

const     int   cMatrix4::ElementCount;

cMatrix4::cMatrix4(float diag) {
    for (int i = 0; i < cMatrix4::ElementCount; ++i)
    {
        Elements[i] = 0.f;
    }

    Elements[0] = diag;
    Elements[1 + 1 * 4] = diag;
    Elements[2 + 2 * 4] = diag;
    Elements[3 + 3 * 4] = diag;
}

cMatrix4 cMatrix4::Multiply(const cMatrix4& other) {
    float data[cMatrix4::ElementCount];
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            float sum = 0.0f;
            for (int e = 0; e < 4; e++) {
                sum += Elements[e + row * 4] * other.Elements[col + e * 4];
            }
            data[col + row * 4] = sum;
        }
    }
    memcpy(Elements, data, cMatrix4::ElementCount * sizeof(float));
    return *this;
}

cMatrix4::cMatrix4(float elements[ElementCount]) {
    memcpy(Elements, elements, ElementCount * 4);
}

cVector3 cMatrix4::Multiply(const cVector3& other) {
    float x = 0.f,
        y = 0.f,
        z = 0.f,
        w = 0.f;
    x = Elements[0] * other.X + Elements[0 + 1 * 4] * other.Y + Elements[0 + 2 * 4] * other.Z + Elements[0 + 3 * 4];
    y = Elements[1] * other.X + Elements[1 + 1 * 4] * other.Y + Elements[1 + 2 * 4] * other.Z + Elements[1 + 3 * 4];
    z = Elements[2] * other.X + Elements[2 + 1 * 4] * other.Y + Elements[2 + 2 * 4] * other.Z + Elements[2 + 3 * 4];
    return cVector3(x, y, z);
}

cVector4 cMatrix4::Multiply(float x, float y, float z, float w)
{
    return {
        x * Elements[0 + 0 * 4] + y * Elements[0 + 1 * 4] + z * Elements[0 + 2 * 4] + w * Elements[0 + 3 * 4],
        x * Elements[1 + 0 * 4] + y * Elements[1 + 1 * 4] + z * Elements[1 + 2 * 4] + w * Elements[1 + 3 * 4],
        x * Elements[2 + 0 * 4] + y * Elements[2 + 1 * 4] + z * Elements[2 + 2 * 4] + w * Elements[2 + 3 * 4],
        x * Elements[3 + 0 * 4] + y * Elements[3 + 1 * 4] + z * Elements[3 + 2 * 4] + w * Elements[3 + 3 * 4] };
}

cMatrix4 cMatrix4::operator*(const cMatrix4 & other) {
    return Multiply(other);
}

cVector3 cMatrix4::operator*(const cVector3 & other) {
    return Multiply(other);
}

cVector3 operator*(cMatrix4 a, const cVector3& b) {
    return a.Multiply(b);
}

cMatrix4 cMatrix4::Translate(const cVector3& vector) {
    cMatrix4 out;
    
    out.Elements[3 + 0 * 4] = vector.X;
    out.Elements[3 + 1 * 4] = vector.Y;
    out.Elements[3 + 2 * 4] = vector.Z;

    return out;
}

cMatrix4 cMatrix4::Translate(const cVector2& vector) {
    cMatrix4 out;

    out.Elements[3 + 0 * 4] = vector.X;
    out.Elements[3 + 1 * 4] = vector.Y;
    return out;

}

cMatrix4 cMatrix4::Scale(const cVector3& vector) {
    cMatrix4 out;

    out.Elements[0] = vector.X;
    out.Elements[1 + 1 * 4] = vector.Y;
    out.Elements[2 + 2 * 4] = vector.Z;
    return out;

}

cMatrix4 cMatrix4::Scale(const cVector2& vector) {
    cMatrix4 out;

    out.Elements[0] = vector.X;
    out.Elements[1 + 1 * 4] = vector.Y;
    return out;

}

cMatrix4 cMatrix4::Scale(float scaleFactor) {
    cMatrix4 out;

    out.Elements[0] = scaleFactor;
    out.Elements[1 + 1 * 4] = scaleFactor;
    out.Elements[2 + 2 * 4] = scaleFactor;
    return out;

}

cMatrix4 cMatrix4::RotateX(float theta) {
    cMatrix4 out;

    float radians = sMaths::ToRadians(theta);
    out.Elements[1 + 1 * 4] = ::cos(radians);
    out.Elements[2 + 2 * 4] = ::cos(radians);
    out.Elements[1 + 2 * 4] = -(::sin(radians));
    out.Elements[2 + 1 * 4] = (::sin(radians));
    return out;

}

cMatrix4 cMatrix4::RotateY(float theta) {
    cMatrix4 out;

    float radians = sMaths::ToRadians(theta);
    out.Elements[0] = ::cos(radians);
    out.Elements[2 + 2 * 4] = ::cos(radians);
    out.Elements[0 + 2 * 4] = (::sin(radians));
    out.Elements[2 + 0 * 4] = -(::sin(radians));
    return out;

}

cMatrix4 cMatrix4::RotateZ(float theta) {
    cMatrix4 out;
    float radians = sMaths::ToRadians(theta);
    out.Elements[0] = ::cos(radians);
    out.Elements[1 + 1 * 4] = ::cos(radians);
    out.Elements[0 + 1 * 4] = -(::sin(radians));
    out.Elements[1 + 0 * 4] = (::sin(radians));
    return out;
}

cVector2 cMatrix4::TransformVector(const cVector2 & vec, const cMatrix4 & mat4)
{
    return cVector2(
        vec.X * mat4.Elements[0]         + vec.Y * mat4.Elements[0 + 1 * 4] + 1 * mat4.Elements[0 + 2 * 4] + 1 * mat4.Elements[0 + 3 * 4],
        vec.X * mat4.Elements[1 + 0 * 4] + vec.Y * mat4.Elements[1 + 1 * 4] + 1 * mat4.Elements[1 + 2 * 4] + 1 * mat4.Elements[1 + 3 * 4]);
}

cMatrix4 cMatrix4::Identity(float diag) {
    return cMatrix4(diag);
}

cVector3 cMatrix4::ScreenToWorld(cMatrix4 projection, cMatrix4 view, const cVector2& screenPos, int viewWidth, int viewHeight) {
    assert(false); // Not implemented yet

    cVector3 pos;

    /*    
    pos.X = 2.f * screenPos.X / static_cast<float>(viewWidth - 1);
    pos.Y = -(2.f * screenPos.Y / static_cast<float>(viewHeight - 1));
    pos.Z = 0;

    view.Invert();
    projection.Invert();
    view.Translate(pos);
    projection.Translate(pos);
    */

    return pos;
}

cMatrix4 cMatrix4::Perpective(float aspectRatio, float foV, float near, float far) {
    cMatrix4 matrix = cMatrix4::Identity();
    matrix.Elements[0] = (1.0f / ::tan(sMaths::ToRadians(0.5f * foV))) / aspectRatio;
    matrix.Elements[1 + 1 * 4] = 1.0f / ::tan(sMaths::ToRadians(0.5f * foV));
    matrix.Elements[2 + 2 * 4] = (near + far) / (near - far);
    matrix.Elements[2 + 3 * 4] = -1.f;
    matrix.Elements[3 + 2 * 4] = (2.f * near * far) / (near - far);

    return matrix;
}

cMatrix4 cMatrix4::Orthographic(float right, float left, float top, float bottom, float far, float near) {
    cMatrix4 matrix = cMatrix4::Identity();
    matrix.Elements[0] = 2.f / (right - left);
    matrix.Elements[1 + 1 * 4] = 2.f / (top - bottom);
    matrix.Elements[2 + 2 * 4] = -2 / (far - near);
    matrix.Elements[3 + 3 * 4] = 1.0f;
    matrix.Elements[3 + 0 * 4] = (left + right) / (left - right); 
    matrix.Elements[3 + 1 * 4] = (bottom + top) / (bottom - top); 
    matrix.Elements[3 + 2 * 4] = (far + near) / (far - near);
    return matrix;
}

cMatrix4 cMatrix4::LookAt(const cVector3 & eyePosition, const cVector3 & lookAtPos, const cVector3 & upVector) {
    cMatrix4 result;
    cVector3 f = cVector3(lookAtPos.X - eyePosition.X, lookAtPos.Y - eyePosition.Y, lookAtPos.Z - eyePosition.Z);
    f = cVector3::Normalize(f);
    cVector3 upCpy = cVector3::Normalize(upVector);

    cVector3 s = cVector3::Cross(f, upVector);
    cVector3 u = cVector3::Cross(s, f);

    result.Elements[0 + 0 * 4] = s.X;
    result.Elements[0 + 1 * 4] = s.Y;
    result.Elements[0 + 2 * 4] = s.Z;

    result.Elements[1 + 0 * 4] = u.X;
    result.Elements[1 + 1 * 4] = u.Y;
    result.Elements[1 + 2 * 4] = u.Z;

    result.Elements[2 + 0 * 4] = -f.X;
    result.Elements[2 + 1 * 4] = -f.Y;
    result.Elements[2 + 2 * 4] = -f.Z;

    return result;
}

/*
Copied from Sparky maths - mat4.cpp
*/
void cMatrix4::Invert() {
    float temp[16];

    temp[0] = Elements[5] * Elements[10] * Elements[15] -
        Elements[5] * Elements[11] * Elements[14] -
        Elements[9] * Elements[6] * Elements[15] +
        Elements[9] * Elements[7] * Elements[14] +
        Elements[13] * Elements[6] * Elements[11] -
        Elements[13] * Elements[7] * Elements[10];

    temp[4] = -Elements[4] * Elements[10] * Elements[15] +
        Elements[4] * Elements[11] * Elements[14] +
        Elements[8] * Elements[6] * Elements[15] -
        Elements[8] * Elements[7] * Elements[14] -
        Elements[12] * Elements[6] * Elements[11] +
        Elements[12] * Elements[7] * Elements[10];

    temp[8] = Elements[4] * Elements[9] * Elements[15] -
        Elements[4] * Elements[11] * Elements[13] -
        Elements[8] * Elements[5] * Elements[15] +
        Elements[8] * Elements[7] * Elements[13] +
        Elements[12] * Elements[5] * Elements[11] -
        Elements[12] * Elements[7] * Elements[9];

    temp[12] = -Elements[4] * Elements[9] * Elements[14] +
        Elements[4] * Elements[10] * Elements[13] +
        Elements[8] * Elements[5] * Elements[14] -
        Elements[8] * Elements[6] * Elements[13] -
        Elements[12] * Elements[5] * Elements[10] +
        Elements[12] * Elements[6] * Elements[9];

    temp[1] = -Elements[1] * Elements[10] * Elements[15] +
        Elements[1] * Elements[11] * Elements[14] +
        Elements[9] * Elements[2] * Elements[15] -
        Elements[9] * Elements[3] * Elements[14] -
        Elements[13] * Elements[2] * Elements[11] +
        Elements[13] * Elements[3] * Elements[10];

    temp[5] = Elements[0] * Elements[10] * Elements[15] -
        Elements[0] * Elements[11] * Elements[14] -
        Elements[8] * Elements[2] * Elements[15] +
        Elements[8] * Elements[3] * Elements[14] +
        Elements[12] * Elements[2] * Elements[11] -
        Elements[12] * Elements[3] * Elements[10];

    temp[9] = -Elements[0] * Elements[9] * Elements[15] +
        Elements[0] * Elements[11] * Elements[13] +
        Elements[8] * Elements[1] * Elements[15] -
        Elements[8] * Elements[3] * Elements[13] -
        Elements[12] * Elements[1] * Elements[11] +
        Elements[12] * Elements[3] * Elements[9];

    temp[13] = Elements[0] * Elements[9] * Elements[14] -
        Elements[0] * Elements[10] * Elements[13] -
        Elements[8] * Elements[1] * Elements[14] +
        Elements[8] * Elements[2] * Elements[13] +
        Elements[12] * Elements[1] * Elements[10] -
        Elements[12] * Elements[2] * Elements[9];

    temp[2] = Elements[1] * Elements[6] * Elements[15] -
        Elements[1] * Elements[7] * Elements[14] -
        Elements[5] * Elements[2] * Elements[15] +
        Elements[5] * Elements[3] * Elements[14] +
        Elements[13] * Elements[2] * Elements[7] -
        Elements[13] * Elements[3] * Elements[6];

    temp[6] = -Elements[0] * Elements[6] * Elements[15] +
        Elements[0] * Elements[7] * Elements[14] +
        Elements[4] * Elements[2] * Elements[15] -
        Elements[4] * Elements[3] * Elements[14] -
        Elements[12] * Elements[2] * Elements[7] +
        Elements[12] * Elements[3] * Elements[6];

    temp[10] = Elements[0] * Elements[5] * Elements[15] -
        Elements[0] * Elements[7] * Elements[13] -
        Elements[4] * Elements[1] * Elements[15] +
        Elements[4] * Elements[3] * Elements[13] +
        Elements[12] * Elements[1] * Elements[7] -
        Elements[12] * Elements[3] * Elements[5];

    temp[14] = -Elements[0] * Elements[5] * Elements[14] +
        Elements[0] * Elements[6] * Elements[13] +
        Elements[4] * Elements[1] * Elements[14] -
        Elements[4] * Elements[2] * Elements[13] -
        Elements[12] * Elements[1] * Elements[6] +
        Elements[12] * Elements[2] * Elements[5];

    temp[3] = -Elements[1] * Elements[6] * Elements[11] +
        Elements[1] * Elements[7] * Elements[10] +
        Elements[5] * Elements[2] * Elements[11] -
        Elements[5] * Elements[3] * Elements[10] -
        Elements[9] * Elements[2] * Elements[7] +
        Elements[9] * Elements[3] * Elements[6];

    temp[7] = Elements[0] * Elements[6] * Elements[11] -
        Elements[0] * Elements[7] * Elements[10] -
        Elements[4] * Elements[2] * Elements[11] +
        Elements[4] * Elements[3] * Elements[10] +
        Elements[8] * Elements[2] * Elements[7] -
        Elements[8] * Elements[3] * Elements[6];

    temp[11] = -Elements[0] * Elements[5] * Elements[11] +
        Elements[0] * Elements[7] * Elements[9] +
        Elements[4] * Elements[1] * Elements[11] -
        Elements[4] * Elements[3] * Elements[9] -
        Elements[8] * Elements[1] * Elements[7] +
        Elements[8] * Elements[3] * Elements[5];

    temp[15] = Elements[0] * Elements[5] * Elements[10] -
        Elements[0] * Elements[6] * Elements[9] -
        Elements[4] * Elements[1] * Elements[10] +
        Elements[4] * Elements[2] * Elements[9] +
        Elements[8] * Elements[1] * Elements[6] -
        Elements[8] * Elements[2] * Elements[5];

    float determinant = Elements[0] * temp[0] + Elements[1] * temp[4] + Elements[2] * temp[8] + Elements[3] * temp[12];
    determinant = 1.0f / determinant;

    for (unsigned i = 0; i < 4 * 4; i++)
        Elements[i] = temp[i] * determinant;
}