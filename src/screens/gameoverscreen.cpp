#include <screens/gameoverscreen.h>
#include <global.h>
#include <keyboard.h>
#include <graphics/colors.h>
#include <screens/levelscreen.h>

void GameOverScreen::Init()
{
}

void GameOverScreen::Unload()
{
}

void GameOverScreen::Resume() 
{
}

void GameOverScreen::Restart()
{
    //Parar esta tela.
    SCREENMANAGER.ToggleUpdate(GAMEOVERSCREEN,false);
    SCREENMANAGER.ToggleRender(GAMEOVERSCREEN,false);
    //Rodar a tela de jogo.
    SCREENMANAGER.ToggleUpdate(LEVELSCREEN,true);
}

void GameOverScreen::GotoTitle()
{
    //Parar esta tela.
    SCREENMANAGER.ToggleUpdate(GAMEOVERSCREEN,false);
    SCREENMANAGER.ToggleRender(GAMEOVERSCREEN,false);
    //Rodar a tela de jogo.
    SCREENMANAGER.ToggleUpdate(TITLESCREEN,true);
    SCREENMANAGER.ToggleRender(TITLESCREEN,true);
}

void GameOverScreen::Update(int delta)
{
}

void GameOverScreen::Render(SDL_Renderer *renderer, int delta)
{
    //Render overlay.
    SDL_SetRenderDrawColor(renderer,0,0,0,235);
    SDL_Rect bounds = {0,0,SCREENWIDTH,SCREENHEIGHT};
    SDL_RenderFillRect(renderer,&bounds);
    //Render points.
    Font::Render(renderer,FONT_NORMAL,"Final Score: " + 
    std::to_string(((LevelScreen*)SCREENMANAGER.GetScreen(LEVELSCREEN))->Points), 
    {SCREENWIDTH/2,SCREENHEIGHT/2},COLR_WHITE,1.2f,FA_Center,0);
    //Render title.
    Font::Render(renderer,FONT_TITLE,"GAME OVER", {SCREENWIDTH/2,64},COLR_WHITE,1,FA_Center,0);
}