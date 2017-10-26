/*
    @author Barney Wilks
*/

#pragma once

#include "../Common.hpp"

namespace b2m2 {
    class cKeyboard {
    private:
        const uint8 *m_keyState;

    public:
        /// Don't call this manually - Should be called automatically when initializing
        /// the engine runtime.
        static void Initalize();

        static bool IsKeyDown(int key);

        static cKeyboard *Get() { static cKeyboard key; return &key; }
    };
}