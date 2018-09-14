#pragma once
#include <interface/menu.h>

class UIControl
{
    friend class UIMenu;
    private:
        SDL_Point _layoutPosition = {0,0};
    public:
        SDL_Point RelativePosition = {0,0};
        UIMenu *Parent = NULL;
        bool IsFocused = false;

        SDL_Point GetActualPosition() const;
        SDL_Rect GetActualBounds() const;
        virtual SDL_Point GetSize() const = 0;
        virtual void Update(int delta) = 0;
        virtual void Render(SDL_Renderer *renderer, int delta) = 0;
};