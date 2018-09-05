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
    //Desenhar um overlay transparente sobre as telas.
    SDL_SetRenderDrawColor(renderer,0,0,0,235);
    SDL_Rect screenBounds = {0,0,SCREENWIDTH,SCREENHEIGHT};
    SDL_RenderFillRect(renderer,&screenBounds);
    //GAME OVER
    Font::Render(renderer, FONT_TITLE,"GAME OVER",{SCREENWIDTH/2,64},COLR_WHITE,FVec2(1),FA_Center,
    0);
    //Pontuacao.
    Font::Render(renderer,FONT_NORMAL,"Score: "+
    std::to_string(((LevelScreen*)SCREENMANAGER.GetScreen(LEVELSCREEN))->Points),
    {SCREENWIDTH/2,SCREENHEIGHT/2},COLR_WHITE,FVec2(1.25),FA_Center,0);
    //Opcoes,
    switch(_current)
    {
        case 0:
        Font::Render(renderer,FONT_NORMAL,"> Try again.", {SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[0]},
        COLR_WHITE,FVec2(1),FA_Center,0);
        Font::Render(renderer,FONT_NORMAL,"Return to title.", {SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[1]},
        COLR_WHITE,FVec2(1),FA_Center,0); 
        break;
        case 1:
        Font::Render(renderer,FONT_NORMAL,"Try again.", {SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[0]},
        COLR_WHITE,FVec2(1),FA_Center,0);
        Font::Render(renderer,FONT_NORMAL,"> Return to title.", {SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[1]},
        COLR_WHITE,FVec2(1),FA_Center,0); 
        break;
    }
}