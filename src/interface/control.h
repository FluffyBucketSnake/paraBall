#pragma once
#include <interface/menu.h>

class UIControl
{
    public:
        SDL_Point Position = {0,0};
        UIMenu *Parent = NULL;
        bool IsFocused = false;

        virtual SDL_Point GetSize() const = 0;
        virtual void Update(int delta) = 0;
        virtual void Render(SDL_Renderer *renderer, int delta) = 0;
};