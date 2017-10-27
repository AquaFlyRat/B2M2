/*
    @author Barney Wilks
*/

#include "Scene.hpp"

using namespace b2m2;

void cScene::Create(vec2 gravity) {
    m_b2World = new b2World({ gravity.x, gravity.y });
}

void cScene::Release() {
    delete m_b2World;
}
