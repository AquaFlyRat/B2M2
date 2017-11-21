#include "Matrix4.hpp"

using namespace CharlieEngine;
using namespace arch;

Matrix4::Matrix4(float diag)
{
    m_handle = new cMatrix4(diag);
}

Matrix4::Matrix4(cMatrix4* matrix)
{
    m_handle = new cMatrix4(matrix->Elements);
}

Matrix4 ^ Matrix4::Multiply(Matrix4 ^ other)
{
    return gcnew Matrix4(&m_handle->Multiply(*other->GetHandle()));
}

Vector3 ^ Matrix4::Multiply(Vector3 ^ other)
{
    cVector3 out = m_handle->Multiply(*other->GetHandle());
    return gcnew Vector3(out.X, out.Y, out.Z);
}

void Matrix4::Invert()
{
    m_handle->Invert();
}

Matrix4 ^ Matrix4::Identity()
{
    return gcnew Matrix4(&cMatrix4::Identity(1.f));
}

Matrix4 ^ Matrix4::Perpective(float aspectRatio, float foV, float far, float near)
{
    return gcnew Matrix4(&cMatrix4::Perpective(aspectRatio, foV, far, near));
}

Matrix4 ^ Matrix4::Orthographic(float right, float left, float top, float bottom, float far, float near)
{
    cMatrix4* ptr = &cMatrix4::Orthographic(right, left, top, bottom, far, near);
    return gcnew Matrix4(ptr);
}

Matrix4 ^ Matrix4::LookAt(const Vector3^ eyePosition, const Vector3^ lookAtPos, Vector3^ upVector)
{
    throw gcnew System::NotImplementedException();
}

Matrix4 ^ Matrix4::Translate(Vector3^ vec3)
{
    return gcnew Matrix4(&cMatrix4::Translate(*vec3->GetHandle()));
}

Matrix4 ^ Matrix4::Translate(Vector2^ vector)
{
    return gcnew Matrix4(&cMatrix4::Translate(*vector->GetHandle()));
}

Matrix4 ^ Matrix4::Scale(Vector3^ vector)
{
    return gcnew Matrix4(&cMatrix4::Scale(*vector->GetHandle()));
}

Matrix4 ^ Matrix4::Scale(float factor)
{
    return gcnew Matrix4(&cMatrix4::Scale(factor));
}

Matrix4 ^ Matrix4::Scale(Vector2^ vector)
{
    return gcnew Matrix4(&cMatrix4::Scale(*vector->GetHandle()));
}

Matrix4 ^ Matrix4::RotateX(float theta)
{
    return gcnew Matrix4(&cMatrix4::RotateX(theta));
}

Matrix4 ^ Matrix4::RotateY(float theta)
{
    return gcnew Matrix4(&cMatrix4::RotateY(theta));
}

Matrix4 ^ Matrix4::RotateZ(float theta)
{
    return gcnew Matrix4(&cMatrix4::RotateZ(theta));
}