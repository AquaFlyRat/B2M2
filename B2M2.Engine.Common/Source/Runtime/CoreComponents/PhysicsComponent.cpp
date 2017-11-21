#include "PhysicsComponent.hpp"

#include "../Scene/Scene.hpp"

using namespace arch;

void cPhysicsComponent::Update(cGameObject *obj) {
    const b2Vec2& vec = m_body->GetPosition();
    m_bOnGround = ApproxEqual(vec.y, obj->Position.Y);
    obj->Position.X = vec.x;
    obj->Position.Y = vec.y;
}

void cPhysicsComponent::Create(cGameObject * obj) {
    vec2& pos = obj->Position;
    
    cScene *scene = obj->ParentScene;
    b2World *world = scene->GetPhysicsWorld();

    b2BodyDef bodyDef;
    if (!m_bStatic) {
        bodyDef.type = b2_dynamicBody;
    }
    bodyDef.position.Set(pos.X, pos.Y);
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(obj->Size.X / 2, obj->Size.Y / 2);
    m_body->CreateFixture(&box, m_fricton);
    m_body->SetFixedRotation(true);
}

cPhysicsComponent::cPhysicsComponent(bool bStatic, float mass): m_mass (mass), m_bStatic(bStatic) {
}
