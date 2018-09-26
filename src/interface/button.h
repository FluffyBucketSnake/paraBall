#pragma once
#include <interface/control.h>
#include <graphics/font.h>
#include <string>

class UIButton : public UIControl
{
    protected:
        virtual void OnClick() {}
    public:
        Font *FontStyle = NULL;
        std::string Text = "";
        SDL_Color NormalColor = {100,100,100,255};
        SDL_Color FocusedColor = {175,175,175,255};
        SDL_Color PressedColor = {255,255,255,255};
        float Scale = 1;
        int Margin = 0;

        void (*ClickEvent)() = NULL;

        virtual SDL_Point GetSize() const;
        virtual void Update(int delta);
        virtual void Render(SDL_Renderer *renderer, int delta);
};