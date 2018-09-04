#pragma once
#include <screens/screen.h>

class TitleScreen : public Screen
{
    public:
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};