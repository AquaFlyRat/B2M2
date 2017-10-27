/*
    @author Barney Wilks
*/

#pragma once

#include <Box2D/Box2D.h>
#include "../../Common.hpp"

namespace b2m2 {
    class cScene {
    private:
        b2World *m_b2World;
    
    public:
        void Create(vec2 gravity);
        void Release();
    };
}
