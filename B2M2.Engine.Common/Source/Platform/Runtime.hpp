/*
    @author Barney Wilks
*/

#pragma once

#include "../Runtime/Systems/System.hpp"
#include <vector>

namespace b2m2 {
    class cRuntime {
    public:
        void Initalize();
        void Shutdown();

        void Update(float delta);
        void AddSystem(cSystem *system);

    private:
        std::vector<cSystem*> m_systems;
    };
}