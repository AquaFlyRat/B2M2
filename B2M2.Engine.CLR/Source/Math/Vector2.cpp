#include "Vector2.hpp"

b2m2::Vector2::Vector2(float x, float y) {
    m_handle = new cVector2(x, y);
}

b2m2::Vector2::Vector2() {
    m_handle = new cVector2();
}