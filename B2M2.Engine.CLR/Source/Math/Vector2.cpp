#include "Vector2.hpp"

using namespace CharlieEngine;

Vector2::Vector2(float x, float y) {
    m_handle = new arch::cVector2(x, y);
}

Vector2::Vector2() {
    m_handle = new arch::cVector2();
}