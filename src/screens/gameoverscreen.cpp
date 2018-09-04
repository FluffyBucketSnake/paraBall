#include <screens/gameoverscreen.h>
#include <global.h>
#include <keyboard.h>
#include <graphics/colors.h>
#include <screens/levelscreen.h>

void GameOverScreen::Restart()
{
    //Resetar tela de jogo.
    ((LevelScreen*)SCREENMANAGER.GetScreen(LEVELSCREEN))->Reset();
    //Parar esta tela.
    SCREENMANAGER.ToggleUpdate(GAMEOVERSCREEN,false);
    SCREENMANAGER.ToggleRender(GAMEOVERSCREEN,false);
    //Rodar a tela de jogo.
    SCREENMANAGER.ToggleUpdate(LEVELSCREEN,true);
}

void GameOverScreen::GotoTitle()
{
    //Resetar tela de jogo.
    ((LevelScreen*)SCREENMANAGER.GetScreen(LEVELSCREEN))->Reset();
    //Parar esta tela.
    SCREENMANAGER.ToggleUpdate(GAMEOVERSCREEN,false);
    SCREENMANAGER.ToggleRender(GAMEOVERSCREEN,false);
    //Rodar a tela de jogo.
    SCREENMANAGER.ToggleUpdate(TITLESCREEN,true);
    SCREENMANAGER.ToggleRender(TITLESCREEN,true);
}

void GameOverScreen::Update(int delta)
{
    //Verificar mudanca de opcao.
    if (Keyboard_Pressed(SDL_SCANCODE_W) && _current != 0)
    {
        //Tocar efeito de som.
        Mix_PlayChannel(-1,SFX_CURSORMOVE,0);
        _current = 0;
    }
    if (Keyboard_Pressed(SDL_SCANCODE_S) && _current != 1)
    {
        //Tocar efeito de som.
        Mix_PlayChannel(-1,SFX_CURSORMOVE,0);
        _current = 1;
    }
    //Verificar se o jogador selecionou continuar.
    if(Keyboard_Pressed(SDL_SCANCODE_SPACE))
    {
        //Tocar efeito de som.
        Mix_PlayChannel(-1,SFX_SELECT,0);
        switch(_current)
        {
            default:
            case 0: Restart(); break;
            case 1: GotoTitle(); break;
        }
        _current = 0;
    }
}

void GameOverScreen::Render(SDL_Renderer *renderer, int delta)
{
    //Calcular o cosseno e guardar.
    int selAlpha = 60 - 30*std::cos(SDL_GetTicks()/200.0f);
    //Desenhar um overlay transparente sobre as telas.
    SDL_SetRenderDrawColor(renderer,0,0,0,235);
    SDL_Rect screenBounds = {0,0,SCREENWIDTH,SCREENHEIGHT};
    SDL_RenderFillRect(renderer,&screenBounds);
    //GAME OVER
    SDL_Point origin = FONT_TITLE->GetTextSize("GAME OVER");
    origin.x /= 2;
    origin.y /= 2;
    FONT_TITLE->Render(renderer,"GAME OVER",{SCREENWIDTH/2,64},COLR_WHITE,FVec2(1),origin,0);
    //Pontuacao.
    std::string scoreText = "Score: " + std::to_string(((LevelScreen*)SCREENMANAGER.GetScreen(LEVELSCREEN))->Points);
    origin = FONT_NORMAL->GetTextSize(scoreText);
    origin.x /= 2;
    origin.y /= 2;
    FONT_NORMAL->Render(renderer,scoreText,{SCREENWIDTH/2,SCREENHEIGHT/2},COLR_WHITE,FVec2(1.25f),origin,0);
    //Tentar novamente.
    origin = FONT_NORMAL->GetTextSize("Try again");
    origin.x /= 2;
    origin.y /= 2;
    if (_current == 0)
    {
        SDL_Rect rect = {SCREENWIDTH/2-origin.x,SCREENHEIGHT-OPTIONY[0]-origin.y-1,origin.x*2+2,origin.y*2+2};
        SDL_SetRenderDrawColor(renderer,255,255,255,selAlpha);
        SDL_RenderFillRect(renderer,&rect);
    }
    FONT_NORMAL->Render(renderer,"Try again",{SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[0]},COLR_WHITE,FVec2(1),origin,0);
    //Sair.
    origin = FONT_NORMAL->GetTextSize("Exit to title");
    origin.x /= 2;
    origin.y /= 2;
    if (_current == 1)
    {
        SDL_Rect rect = {SCREENWIDTH/2-origin.x-1,SCREENHEIGHT-OPTIONY[1]-origin.y-1,origin.x*2+3,origin.y*2+2};
        SDL_SetRenderDrawColor(renderer,255,255,255,selAlpha);
        SDL_RenderFillRect(renderer,&rect);
    }
    FONT_NORMAL->Render(renderer,"Exit to title",{SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[1]},COLR_WHITE,FVec2(1),origin,0);
}