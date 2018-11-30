#include <keyboard.h>

Uint8* Keyboard::CurrentState;
Uint8* Keyboard::LastState;
const Uint8* Keyboard::SDLState;
int Keyboard::NumberOfKeys;

void Keyboard::Init()
{
    //Guardar ponteiro principal.
    NumberOfKeys = 0;
    SDLState = SDL_GetKeyboardState(&NumberOfKeys);
    //Criar marca-estados.
    CurrentState = new Uint8[NumberOfKeys];
    LastState = new Uint8[NumberOfKeys];
    //Guardar estado atual.
    memcpy(CurrentState,SDLState,NumberOfKeys);
}

void Keyboard::Update()
{
    //Guardar estado anterior.
    memcpy(LastState,CurrentState,NumberOfKeys);
    //Receber estado atual.
    memcpy(CurrentState,SDLState,NumberOfKeys);
}

void Keyboard::Quit()
{
    //Liberar memoria.
    delete[] CurrentState;
    delete[] LastState;
}

bool Keyboard::IsDown(SDL_Scancode key)
{
    return CurrentState[key];
}

bool Keyboard::IsUp(SDL_Scancode key)
{
    return !CurrentState[key];
}

bool Keyboard::Pressed(SDL_Scancode key)
{
    return CurrentState[key] && !LastState[key];
}

bool Keyboard::Released(SDL_Scancode key)
{
    return LastState[key] && !CurrentState[key];
}