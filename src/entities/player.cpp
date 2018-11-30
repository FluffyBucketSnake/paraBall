#include <entities/player.h>

Player::Player()
{
    //Definir tamanho do jogador.
    bBox.w = 48;
    bBox.h = 8;
    //Definir origem da caixa.
    bBoxOrigin.x = bBox.w/2;
    bBoxOrigin.y = bBox.h/2;
    //Definir posicao inicial.
    position.x = 0;
    position.y = 0;
    bBox.x = position.x - bBoxOrigin.x;
    bBox.y = position.y - bBoxOrigin.y;
}

void Player::Update(int delta)
{
    //Cuidar da entrada.
    HandleInput();
    //Cuidar do movimento.
    HandleMovement(delta);
}

void Player::Render(SDL_Renderer* renderer, int delta)
{
    //Desenhar jogador.
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&bBox);
}

void Player::HandleInput()
{
    //Receber entrada.
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    movingLeft = state[SDL_SCANCODE_A];
    movingRight = state[SDL_SCANCODE_D];
}

void Player::HandleMovement(int delta)
{
    //Guardar a velocidade temporariamente.
    FVec2 oldspeed = Speed;
    //Verificar se o jogador quer se mover.
    if (movingLeft && !movingRight)
        Speed.x -= ACCELERATION * delta * 0.001f;
    else if (movingRight && !movingLeft)
        Speed.x += ACCELERATION * delta * 0.001f;
    else
    {
        if (std::abs(Speed.x) - DEACCELERATION * delta * 0.001f > 0)
            Speed.x -= DEACCELERATION * ((0 < Speed.x) - (Speed.x < 0)) * delta * 0.001f;
        else
            Speed.x = 0;
    }
    //Limitar velocidade.
    if (std::abs(Speed.x) > MAXHSPEED)
        Speed.x = MAXHSPEED * ((0 < Speed.x) - (Speed.x < 0));
    //Aplicar velocidade.
    SetPosition(position + (Speed * delta * 0.001f));
}