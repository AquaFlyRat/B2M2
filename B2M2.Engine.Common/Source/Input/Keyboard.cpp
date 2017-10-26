#include "Keyboard.hpp"

#include <SDL2/SDL.h>

using namespace b2m2;

void cKeyboard::Initalize()
{
    cKeyboard *keyboard = cKeyboard::Get();
    keyboard->m_keyState = SDL_GetKeyboardState(NULL);
}

bool cKeyboard::IsKeyDown(int key)
{
    cKeyboard *keyboard = cKeyboard::Get();
    return keyboard->m_keyState[key];
}
