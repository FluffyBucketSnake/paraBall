#include <screens/titlescreen.h>
#include <interface/button.h>
#include <keyboard.h>
#include <graphics/colors.h>
#include <global.h>

void TitleScreen::Play()
{
    //Parar titulo.
    SCREENMANAGER.ToggleUpdate(TITLESCREEN,false);
    SCREENMANAGER.ToggleRender(TITLESCREEN,false);
    //Rodar fase.
    SCREENMANAGER.ToggleUpdate(LEVELSCREEN,true);
}

void TitleScreen::Exit()
{
    
}

void TitleScreen::Init()
{
    //Menu.
    menu.Position = {64,160};
    //Play button.
    UIButton *playBtn = new UIButton;
    playBtn->Text = "Play";
    playBtn->Margin = 2;
    playBtn->FontStyle = FONT_NORMAL;
    playBtn->ClickEvent = &Play;
    menu.AddChild(playBtn);
    //Exit button.
    UIButton *exitBtn = new UIButton;
    exitBtn->Text = "Exit";
    exitBtn->Margin = 2;
    exitBtn->FontStyle = FONT_NORMAL;
    exitBtn->ClickEvent = &Exit;
    menu.AddChild(exitBtn);
}

void TitleScreen::Unload()
{
    menu.ClearChildren();
}

void TitleScreen::Resume()
{
    menu.SetFocus(0);
}

void TitleScreen::Update(int delta)
{
    menu.Update(delta);
}

void TitleScreen::Render(SDL_Renderer *renderer, int delta)
{
    //Desenhar um overlay transparente sobre as telas.
    SDL_SetRenderDrawColor(renderer,0,0,0,235);
    SDL_Rect screenBounds = {0,0,SCREENWIDTH,SCREENHEIGHT};
    SDL_RenderFillRect(renderer,&screenBounds);
    //Calcular o cosseno e guardar.
    float ccos = 0;//std::cos(SDL_GetTicks()/200.0f);
    //Renderizar titulo.
    Font::Render(renderer,FONT_TITLE,TITLE,{SCREENWIDTH/2,64},COLR_WHITE,FVec2(1),FA_Center,
    3.25f*ccos);
    //Renderizar menu.
    menu.Render(renderer,delta);
    //Versao.
    Font::Render(renderer,FONT_NORMAL,"v." + std::string(VERSION),
    {SCREENWIDTH,SCREENHEIGHT},COLR_WHITE,FVec2(1),FA_BottomRight,0);
}