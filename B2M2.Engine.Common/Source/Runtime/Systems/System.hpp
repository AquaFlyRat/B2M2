/*
    @author Barney Wilks
*/

#pragma once

namespace b2m2 {
    class cSystem {
    public:
        virtual void Update(float dt) = 0;
        virtual void Create() = 0;
        virtual void SendMessage();
    };
}