#include <keyboard.h>

const Uint8* Keyboard_CurrentState;
const Uint8* Keyboard_LastState;
const Uint8* Keyboard_SDLState;
int Keyboard_KeyNumber;

void Keyboard_Init()
{
    //Guardar ponteiro principal.
    Keyboard_KeyNumber = 0;
    Keyboard_SDLState = SDL_GetKeyboardState(&Keyboard_KeyNumber);
    //Criar marca-estados.
    _keyboard_CurrentState = new Uint8[Keyboard_KeyNumber];
    _keyboard_LastState = new Uint8[Keyboard_KeyNumber];
    //Guardar estado atual.
    memcpy(_keyboard_CurrentState,Keyboard_SDLState,Keyboard_KeyNumber);
    //Redirecionar ponteiros globais.
    Keyboard_CurrentState = _keyboard_CurrentState;
    Keyboard_LastState = _keyboard_LastState;
}

void Keyboard_Update()
{
    //Guardar estado anterior.
    memcpy(_keyboard_LastState,Keyboard_CurrentState,Keyboard_KeyNumber);
    //Receber estado atual.
    memcpy(_keyboard_CurrentState,Keyboard_SDLState,Keyboard_KeyNumber);
}

void Keyboard_Quit()
{
    //Liberar memoria.
    delete[] Keyboard_CurrentState;
    delete[] Keyboard_LastState;
}

bool Keyboard_IsDown(SDL_Scancode key)
{
    return Keyboard_CurrentState[key];
}

bool Keyboard_IsUp(SDL_Scancode key)
{
    return !Keyboard_CurrentState[key];
}

bool Keyboard_Pressed(SDL_Scancode key)
{
    return Keyboard_CurrentState[key] && !Keyboard_LastState[key];
}

bool Keyboard_Released(SDL_Scancode key)
{
    return Keyboard_LastState[key] && !Keyboard_CurrentState[key];
}