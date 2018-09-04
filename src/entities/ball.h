#pragma once
#include <entities/entity.h>

class Ball : public Entity
{
public:
    const float INERTIA = 1;
    const float GRAVITY = 1;

    FVec2 Speed;

    Ball();
    void Update(int delta);
    void Render(SDL_Renderer* renderer, int delta);
};
