#include "Vector3.hpp"

b2m2::Vector3::Vector3(cVector3 * vecptr): ManagedClass(vecptr)
{
}

b2m2::Vector3::Vector3()
{
    m_handle = new b2m2::cVector3();
}

b2m2::Vector3::Vector3(float x, float y, float z)
{
    m_handle = new b2m2::cVector3(x, y, z);
}
