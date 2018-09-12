#include <screens/gameoverscreen.h>
#include <global.h>
#include <keyboard.h>
#include <graphics/colors.h>
#include <screens/levelscreen.h>
#include <interface/button.h>

void GameOverScreen::Init()
{
    //Try again.
    UIButton *button = new UIButton;
    button->Text = "Try again.";
    button->FontStyle = FONT_NORMAL;
    button->Position = {SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[0]};
    button->Align = FA_Center;
    button->Event_Pressed = &Restart;
    menu.AddChild(button);
    //Go to  title.
    button = new UIButton;
    button->Text = "Go to title.";
    button->FontStyle = FONT_NORMAL;
    button->Position = {SCREENWIDTH/2,SCREENHEIGHT-OPTIONY[1]};
    button->Align = FA_Center;
    button->Event_Pressed = &GotoTitle;
    menu.AddChild(button);
}

void GameOverScreen::Unload()
{
    menu.ClearChildren();
}

void GameOverScreen::Resume() 
{
    menu.SetFocus(0);
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
    //Update menu.
    menu.Update(delta);
}

void GameOverScreen::Render(SDL_Renderer *renderer, int delta)
{
    //Render overlay.
    SDL_SetRenderDrawColor(renderer,0,0,0,235);
    SDL_Rect bounds = {0,0,SCREENWIDTH,SCREENHEIGHT};
    SDL_RenderFillRect(renderer,&bounds);
    //Render menu.
    menu.Render(renderer,delta);
    //Render points.
    Font::Render(renderer,FONT_NORMAL,"Final Score: " + 
    std::to_string(((LevelScreen*)SCREENMANAGER.GetScreen(LEVELSCREEN))->Points), 
    {SCREENWIDTH/2,SCREENHEIGHT/2},COLR_WHITE,1.2f,FA_Center,0);
    //Render title.
    Font::Render(renderer,FONT_TITLE,"GAME OVER", {SCREENWIDTH/2,64},COLR_WHITE,1,FA_Center,0);
}