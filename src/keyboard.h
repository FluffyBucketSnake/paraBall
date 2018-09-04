#pragma once
#include <SDL2/SDL.h>

extern const Uint8* Keyboard_CurrentState;
extern const Uint8* Keyboard_LastState;
extern const Uint8* Keyboard_SDLState;
extern int Keyboard_KeyNumber;

static Uint8* _keyboard_CurrentState;
static  Uint8* _keyboard_LastState;

void Keyboard_Init();
void Keyboard_Update();
void Keyboard_Quit();
bool Keyboard_IsDown(SDL_Scancode key);
bool Keyboard_IsUp(SDL_Scancode key);
bool Keyboard_Pressed(SDL_Scancode key);
bool Keyboard_Released(SDL_Scancode key);