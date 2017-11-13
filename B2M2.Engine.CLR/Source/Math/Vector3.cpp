#include "Vector3.hpp"

using namespace CharlieEngine;

Vector3::Vector3(b2m2::cVector3 * vecptr): ManagedClass(vecptr)
{
}

Vector3::Vector3()
{
    m_handle = new b2m2::cVector3();
}

Vector3::Vector3(float x, float y, float z)
{
    m_handle = new b2m2::cVector3(x, y, z);
}
