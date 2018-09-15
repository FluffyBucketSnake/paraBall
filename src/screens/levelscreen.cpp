#include <screens/levelscreen.h>
#include <graphics/colors.h>
#include <global.h>

LevelScreen::LevelScreen()
{
    Reset();
}

void LevelScreen::Resume()
{
    //Definir posicoes iniciais.
    Reset();
}

void LevelScreen::Reset()
{
    //Redefinir contador.
    Points = 0;
    //Redefinir jogador.
    player.SetPosition(SCREENWIDTH/2,SCREENHEIGHT-32);
    player.Speed = FVec2(0,0);
    //Redefinir bola.
    ball.SetPosition(SCREENWIDTH/2,SCREENHEIGHT/2);
    ball.Speed = FVec2(0,0);
}

void LevelScreen::Point()
{
    //Marcar o ponto.
    Points++;
    //Tocar som de ponto.
    Mix_PlayChannel(-1,SFX_POINT,0);
}

void LevelScreen::Lose()
{
    //Tocar som de derrota.
    Mix_PlayChannel(-1,SFX_DEATH,0);
    //Parar fase.
    SCREENMANAGER.ToggleUpdate(LEVELSCREEN,false);
    //Mostrar game over.
    SCREENMANAGER.ToggleUpdate(GAMEOVERSCREEN,true);
    SCREENMANAGER.ToggleRender(GAMEOVERSCREEN,true);
}

void LevelScreen::HandlePSCollision()
{
    //Manter o jogador na tela.
    if (player.GetBBox()->x < 0)
    {
        player.SetPosition(player.GetBBox()->w/2,player.GetPosition().y);
        player.Speed.x *= -player.BOUNCINESS;
        Mix_PlayChannel(-1,SFX_COLLISION,0);
    }
    if (player.GetBBox()->x + player.GetBBox()->w > SCREENWIDTH)
    {
        player.SetPosition(SCREENWIDTH - player.GetBBox()->w/2, player.GetPosition().y);
        player.Speed.x *= -player.BOUNCINESS;
        Mix_PlayChannel(-1,SFX_COLLISION,0);
    }
}

void LevelScreen::HandleBSCollision()
{
    //Checar colisao com a tela.
    //Esquerda
    if (ball.GetBBox()->x < 0)
    {
        ball.SetPosition(ball.GetBBox()->w/2,ball.GetPosition().y);
        ball.Speed.x *= -1;
        Mix_PlayChannel(-1,SFX_COLLISION,0);
    }
    //Direita
    if (ball.GetBBox()->x + ball.GetBBox()->w > SCREENWIDTH)
    {
        ball.SetPosition(SCREENWIDTH - ball.GetBBox()->w/2,ball.GetPosition().y);
        ball.Speed.x *= -1;
        Mix_PlayChannel(-1,SFX_COLLISION,0);
    }
    //Cima
    if (ball.GetBBox()->y < 0)
    {
        ball.SetPosition(ball.GetPosition().x, ball.GetBBox()->h/2);
        ball.Speed.y *= -0.5;
        Mix_PlayChannel(-1,SFX_COLLISION,0);
    }
    //Baixo
    //Se a bola caiu alem da tela, o jogador perdeu.
    if (ball.GetBBox()->y > SCREENHEIGHT)
        Lose();
}

void LevelScreen::HandleBPCollision()
{
    //Calcular a caixa projetada da bola.
    SDL_Rect ballBBox = *ball.GetBBox();
    int y = ballBBox.y-ball.Speed.y;
    int h = ballBBox.h+ball.Speed.y;
    SDL_Rect projBall = {ballBBox.x,y,ballBBox.w,h};
    if (SDL_HasIntersection(player.GetBBox(),&projBall))
    {
        //Colocar a bola para cima do jogador.
        ball.SetPosition(ball.GetPosition().x,player.GetBBox()->y - ball.GetOrigin().y);
        //Definir novas velocidades.
        float newHSpeed = (std::rand()%320 - 160);
        float newVSpeed = (std::rand()%32 - 16) - 480;
        ball.Speed = FVec2(newHSpeed,newVSpeed);
        //Marcar ponto.
        Point();
    }
}

void LevelScreen::Update(int delta)
{
    //Loopar jogador e bola.
    player.Update(delta);
    ball.Update(delta);
    //Checar colisao.
    HandlePSCollision();
    HandleBPCollision();
    HandleBSCollision();
}

void LevelScreen::Render(SDL_Renderer* renderer, int delta)
{
    //Renderizar jogador e bola.
    player.Render(renderer,delta);
    ball.Render(renderer,delta);
    //Apresentar texto.
    Font::Render(renderer,FONT_NORMAL,std::to_string(Points),{8,8},COLR_WHITE,FVec2(1.5f),FA_TopLeft,0);
}