#include "Keyboard.hpp"

#include <SDL2/SDL.h>

using namespace b2m2;

void b2m2::cKeyboard::Initalize()
{
    cKeyboard *keyboard = cKeyboard::Get();
    keyboard->m_keyState = SDL_GetKeyboardState(NULL);
}

bool cKeyboard::IsKeyDown(int key)
{
    cKeyboard *keyboard = cKeyboard::Get();
    return keyboard->m_keyState[key];
}

char cKeyboard::GetASCIIChar(SDL_KeyboardEvent evt)
{
    int scan = evt.keysym.scancode;
    char _ascii;

    switch (scan) {
    case SDL_SCANCODE_0: _ascii = '0'; break;
    case SDL_SCANCODE_1: _ascii = '1'; break;
    case SDL_SCANCODE_2: _ascii = '2'; break;
    case SDL_SCANCODE_3: _ascii = '3'; break;
    case SDL_SCANCODE_4: _ascii = '4'; break;
    case SDL_SCANCODE_5: _ascii = '5'; break;
    case SDL_SCANCODE_6: _ascii = '6'; break;
    case SDL_SCANCODE_7: _ascii = '7'; break;
    case SDL_SCANCODE_8: _ascii = '8'; break;
    case SDL_SCANCODE_9: _ascii = '9'; break;
    case SDL_SCANCODE_A: _ascii = 'a'; break;
    case SDL_SCANCODE_B: _ascii = 'b'; break;
    case SDL_SCANCODE_C: _ascii = 'c'; break;
    case SDL_SCANCODE_D: _ascii = 'd'; break;
    case SDL_SCANCODE_E: _ascii = 'e'; break;
    case SDL_SCANCODE_F: _ascii = 'f'; break;
    case SDL_SCANCODE_G: _ascii = 'g'; break;
    case SDL_SCANCODE_H: _ascii = 'h'; break;
    case SDL_SCANCODE_I: _ascii = 'i'; break;
    case SDL_SCANCODE_J: _ascii = 'j'; break;
    case SDL_SCANCODE_K: _ascii = 'k'; break;
    case SDL_SCANCODE_L: _ascii = 'l'; break;
    case SDL_SCANCODE_M: _ascii = 'm'; break;
    case SDL_SCANCODE_N: _ascii = 'n'; break;
    case SDL_SCANCODE_O: _ascii = 'o'; break;
    case SDL_SCANCODE_P: _ascii = 'p'; break;
    case SDL_SCANCODE_Q: _ascii = 'q'; break;
    case SDL_SCANCODE_R: _ascii = 'r'; break;
    case SDL_SCANCODE_S: _ascii = 's'; break;
    case SDL_SCANCODE_T: _ascii = 't'; break;
    case SDL_SCANCODE_U: _ascii = 'u'; break;
    case SDL_SCANCODE_V: _ascii = 'v'; break;
    case SDL_SCANCODE_W: _ascii = 'w'; break;
    case SDL_SCANCODE_X: _ascii = 'x'; break;
    case SDL_SCANCODE_Y: _ascii = 'y'; break;
    case SDL_SCANCODE_Z: _ascii = 'z'; break;
    
    case SDL_SCANCODE_SPACE: _ascii = ' '; break;
    case SDL_SCANCODE_PERIOD: _ascii = '.'; break;
    case SDL_SCANCODE_COMMA: _ascii = ','; break;
    case SDL_SCANCODE_SLASH: _ascii = '/'; break;
    default: _ascii = 0;
    }

    if (isalpha(_ascii)) {
        if (evt.keysym.mod & KMOD_SHIFT || evt.keysym.mod & KMOD_CAPS) _ascii = toupper(_ascii);
    }

    return _ascii;
}
