/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"
#include <SDL2/SDL.h>

namespace b2m2 {
    class cKeyboard {
    private:
        const uint8 *m_keyState;

    public:
        /// Don't call this manually - Should be called automatically when initializing
        /// the engine runtime.
        static void Initalize();

        static bool IsKeyDown(int key);

        static char GetASCIIChar(SDL_KeyboardEvent evt);

        static cKeyboard *Get() { static cKeyboard key; return &key; }
    };
}