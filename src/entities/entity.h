#pragma once
#include <SDL2/SDL.h>
#include <fvec2.h>

class Entity
{
protected:
    FVec2 position;
    SDL_Point bBoxOrigin;
    SDL_Rect bBox;
public:
    FVec2 GetPosition()
    {
        return position;
    }
    SDL_Point GetOrigin()
    {
        return bBoxOrigin;
    }
    const SDL_Rect* GetBBox()
    {
        return &bBox;
    }
    virtual void SetPosition(float newX, float newY)
    {
        position.x = newX;
        position.y = newY;
        bBox.x = newX - bBoxOrigin.x;
        bBox.y = newY - bBoxOrigin.y;
    }
    virtual void SetPosition(FVec2 newPosition)
    {
        position = newPosition;
        bBox.x = newPosition.x - bBoxOrigin.x;
        bBox.y = newPosition.y - bBoxOrigin.y;
    }
    virtual void Update(int delta) = 0;
    virtual void Render(SDL_Renderer* renderer, int delta) = 0;
};
