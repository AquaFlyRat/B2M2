/*
    @author Barney Wilks
*/

#pragma once

#include "../Scene/GameObject.hpp"

#include <Box2D/Box2D.h>

namespace b2m2 {
    struct cPhysicsComponent : public cComponent {
        virtual void Update(cGameObject *obj);
        virtual void Create(cGameObject *obj);

        cPhysicsComponent(bool bStatic, float mass);

        float GetMass() { return m_mass; }
        float GetDensity() { return m_density; }
        float GetFriction() { return m_fricton; }

        bool IsOnGround() { return m_bOnGround; }

        void SetMass(float mass) { m_mass = mass; }
        void SetDensity(float density) { m_density = density; }
        void SetFriction(float friction) { m_fricton = friction; };
        b2Body *GetBody() { return m_body; }
    private:
        b2Body *m_body;
        float m_mass, m_density = 0.f, m_fricton = .3f;
        bool m_bStatic, m_bOnGround;
    };
}