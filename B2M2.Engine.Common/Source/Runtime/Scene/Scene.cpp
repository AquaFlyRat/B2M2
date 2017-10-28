/*
    @author Barney Wilks
*/

#include "Scene.hpp"
#include <SDL2/SDL.h>

using namespace b2m2;

void cScene::Create(vec2 gravity) {
    m_b2World = new b2World({ gravity.x, gravity.y });
}

void cScene::Release() {
    for (cGameObject* obj : m_objects) {
        delete obj;
        obj = nullptr;
    }

    delete m_b2World;
}

void cScene::Update() {
    int velocityIterations = 8;
    int positionIterations = 3;    m_b2World->Step(1.f/60.f, velocityIterations, positionIterations);
    for (cGameObject *obj : m_objects) obj->Update();
}
