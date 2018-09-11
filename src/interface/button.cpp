#include <interface/button.h>
#include <graphics/colors.h>
#include <keyboard.h>
#include <global.h>

SDL_Point UIButton::GetSize() const
{
    return FontStyle->GetTextSize(Text);
}

void UIButton::Update(int delta)
{
    if (Keyboard_Released(SDL_SCANCODE_SPACE) && IsFocused && Event_Pressed != NULL)
    {
        Mix_PlayChannel(-1,SFX_SELECT,0);
        Event_Pressed();
    }
}

void UIButton::Render(SDL_Renderer *renderer, int delta)
{
    //Calculate actual position.
    SDL_Point actualPosition;
    if (Parent != NULL)
        actualPosition = {Position.x + Parent->Position.x,Position.y + Parent->Position.y};
    else
        actualPosition = {Position.x, Position.y};
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
    Font::Render(renderer,FontStyle,Text,actualPosition,color,Scale,Align,0);
}