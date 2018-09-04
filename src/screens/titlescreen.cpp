#include <screens/titlescreen.h>
#include <keyboard.h>
#include <graphics/colors.h>
#include <global.h>

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
    SDL_Point origin = FONT_TITLE->GetTextSize(TITLE);
    origin.x /= 2;
    origin.y /= 2;
    FONT_TITLE->Render(renderer,TITLE,{SCREENWIDTH/2,64},COLR_WHITE,FVec2(1),origin,3.25f*ccos);
    //Renderizar comando.
    origin = FONT_NORMAL->GetTextSize("Press space to start.");
    origin.x /= 2;
    origin.y /= 2;
    FVec2 size;
    FONT_NORMAL->Render(renderer,"Press <space> to start",{SCREENWIDTH/2,SCREENHEIGHT-64},COLR_WHITE,FVec2(1),origin,-ccos);
    //Versao.
    origin = FONT_NORMAL->GetTextSize("v." + std::string(VERSION));
    FONT_NORMAL->Render(renderer,"v." + std::string(VERSION),{SCREENWIDTH-origin.x,SCREENHEIGHT-origin.y},COLR_WHITE);
}