#include <screens/titlescreen.h>
#include <keyboard.h>
#include <graphics/colors.h>
#include <global.h>

void TitleScreen::Init()
{

}

void TitleScreen::Unload()
{

}

void TitleScreen::Resume()
{

}

void TitleScreen::Pause()
{
    
}

void TitleScreen::Update(int delta)
{
    if (Keyboard_Pressed(SDL_SCANCODE_SPACE))
    {
        //Tocar efeito de som.
        Mix_PlayChannel(-1,SFX_SELECT,0);
        //Parar titulo.
        SCREENMANAGER.ToggleUpdate(TITLESCREEN,false);
        SCREENMANAGER.ToggleRender(TITLESCREEN,false);
        //Rodar fase.
        SCREENMANAGER.ToggleUpdate(LEVELSCREEN,true);
    }
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
    //Renderizar comando.
    Font::Render(renderer,FONT_NORMAL,"Press <space> to start",{SCREENWIDTH/2,SCREENHEIGHT-64},
    COLR_WHITE,FVec2(1),FA_Center,-ccos);
    //Versao.
    Font::Render(renderer,FONT_NORMAL,"v." + std::string(VERSION),
    {SCREENWIDTH,SCREENHEIGHT},COLR_WHITE,FVec2(1),FA_BottomRight,0);
}