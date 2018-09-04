#pragma once
#include <SDL2/SDL.h>

class Screen
{
    public:
        virtual void Update(int delta) = 0;
        virtual void Render(SDL_Renderer* renderer, int delta) = 0;
};