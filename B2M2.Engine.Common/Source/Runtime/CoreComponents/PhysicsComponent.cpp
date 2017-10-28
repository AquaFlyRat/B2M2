#include "PhysicsComponent.hpp"

#include "../Scene/Scene.hpp"

using namespace b2m2;

void cPhysicsComponent::Update(cGameObject *obj) {
    const b2Vec2& vec = m_body->GetPosition();
    m_bOnGround = ApproxEqual(vec.y, obj->Position.y);
    obj->Position.x = vec.x;
    obj->Position.y = vec.y;
}

void cPhysicsComponent::Create(cGameObject * obj) {
    vec2& pos = obj->Position;
    
    cScene *scene = obj->ParentScene;
    b2World *world = scene->GetPhysicsWorld();

    b2BodyDef bodyDef;
    if (!m_bStatic) {
        bodyDef.type = b2_dynamicBody;
    }
    bodyDef.position.Set(pos.x, pos.y);
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(obj->Size.x / 2, obj->Size.y / 2);
    m_body->CreateFixture(&box, m_fricton);
    m_body->SetFixedRotation(true);
}

cPhysicsComponent::cPhysicsComponent(bool bStatic, float mass): m_mass (mass), m_bStatic(bStatic) {
}
