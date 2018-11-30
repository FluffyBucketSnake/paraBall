#pragma once
#include <SDL2/SDL.h>

namespace Keyboard
{
    extern Uint8* CurrentState;
    extern Uint8* LastState;
    extern const Uint8* SDLState;
    extern int NumberOfKeys;

    void Init();
    void Update();
    void Quit();
    bool IsDown(SDL_Scancode key);
    bool IsUp(SDL_Scancode key);
    bool Pressed(SDL_Scancode key);
    bool Released(SDL_Scancode key);
}