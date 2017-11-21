#include "Vector3.hpp"

using namespace CharlieEngine;

Vector3::Vector3(arch::cVector3 * vecptr): ManagedClass(vecptr)
{
}

Vector3::Vector3()
{
    m_handle = new arch::cVector3();
}

Vector3::Vector3(float x, float y, float z)
{
    m_handle = new arch::cVector3(x, y, z);
}
