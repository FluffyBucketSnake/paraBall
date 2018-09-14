#include <interface/control.h>

SDL_Point UIControl::GetActualPosition() const
{
    if (Parent != NULL)
        return {RelativePosition.x + _layoutPosition.x, RelativePosition.y + _layoutPosition.y};
    else
        return RelativePosition;
}

SDL_Rect UIControl::GetActualBounds() const
{
    SDL_Point size = GetSize();
    if (Parent != NULL)
        return {RelativePosition.x + _layoutPosition.x, RelativePosition.y + _layoutPosition.y,size.x,size.y};
    else
        return {RelativePosition.x,RelativePosition.y,size.x,size.y};
}