#pragma once
#include <entities/entity.h>

class Player : public Entity
{
private:
    Uint8 movingLeft, movingRight;  //Estados de movimento do jogador.

    void HandleInput();
    void HandleMovement(int delta);
public:
    const float ACCELERATION = 1600;   //Aceleracao do jogador.
    const float DEACCELERATION = 1600;  //Deaceleracao de jogador.
    const float MAXHSPEED = 400;    //Velocidade horizontal maxima.
    const float BOUNCINESS = 0.75f; //Elasticidade do jogador.
    const float INERTIA = 2;    //Inercia do jogador;

    FVec2 Speed;

    Player();
    void Update(int delta);
    void Render(SDL_Renderer* renderer, int delta);
};
