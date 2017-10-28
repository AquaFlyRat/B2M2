/*
    @author Barney Wilks
*/

#pragma once

#include <Box2D/Box2D.h>

#include "../../Common.hpp"
#include "GameObject.hpp"

namespace b2m2 {
    class cScene {
    private:
        b2World *m_b2World;
        std::vector<cGameObject*> m_objects;

    public:
        void Create(vec2 gravity);
        void Release();

        void Update();

        void AddObject(cGameObject *obj) {
            obj->ParentScene = this;
            obj->Create();
            m_objects.push_back(obj);
        }

        b2World *GetPhysicsWorld() { return m_b2World; }
    };
}
