#include <entities/ball.h>

Ball::Ball()
{
    //Criar caixa de colisao da bola.
    bBox.w = 10;
    bBox.h = 10;
    //Definir origem da caixa da bola.
    bBoxOrigin.x = bBox.w/2;
    bBoxOrigin.y = bBox.h/2;
    //Definir posicao.
    position.x = 0;
    position.y = 0;
    bBox.x = position.x - bBoxOrigin.x;
    bBox.y = position.y - bBoxOrigin.y;
}

void Ball::Update(int delta)
{
    //Gravidade.
    Speed.y += delta;
    //Mover a bola.
    position += Speed * delta * 0.001f;
    bBox.x = position.x - bBoxOrigin.x;
    bBox.y = position.y - bBoxOrigin.y;
}

void Ball::Render(SDL_Renderer* renderer, int delta)
{
    //Renderizar a bola.
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&bBox);
}