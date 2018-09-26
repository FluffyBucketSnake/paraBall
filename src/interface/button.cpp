#include <interface/button.h>
#include <graphics/colors.h>
#include <keyboard.h>
#include <global.h>

SDL_Point UIButton::GetSize() const
{
    SDL_Point textSize = FontStyle->GetTextSize(Text);
    return {textSize.x + 2*Margin, textSize.y + 2*Margin};
}

void UIButton::Update(int delta)
{
    if (Keyboard_Released(SDL_SCANCODE_SPACE) && IsFocused)
    {
        Mix_PlayChannel(-1,SFX_SELECT,0);
        if (ClickEvent != NULL)
            ClickEvent();
        OnClick();
    }
}

void UIButton::Render(SDL_Renderer *renderer, int delta)
{
    //Calculate the color.
    SDL_Color color = NormalColor;
    if (IsFocused)
    {
        if (Keyboard_IsDown(SDL_SCANCODE_SPACE))
            color = PressedColor;
        else
            color = FocusedColor;
    }
    //Render the result text.
    SDL_Point actualPos = GetActualPosition();
    Font::Render(renderer,FontStyle,Text,{actualPos.x + Margin, actualPos.y + Margin},color,Scale,FA_TopLeft,0);
}