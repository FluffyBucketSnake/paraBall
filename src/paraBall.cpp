#include <paraBall.h>
#include <global.h>
#include <keyboard.h>
#include <screens/titlescreen.h>
#include <screens/levelscreen.h>
#include <screens/gameoverscreen.h>
#include <iostream>

void paraBall::Init()
{
    //Reference the game application. TODO: clean this shit.
    GAME = this;
    Keyboard::Init();
    //Container test.
    container.Controls().push_back(new ControlBase({0,0},{64,16},{2,2,2,2}));
    container.Controls().push_back(new ControlBase({0,0},{64,16},{2,2,2,2}));
    container.UpdateLayout();
}

void paraBall::Load()
{
}

void paraBall::Update(int delta)
{
    Keyboard::Update();
    container.Update(delta);
}

void paraBall::Render(int delta)
{   
    //Limpar tela.
    SDL_SetRenderDrawColor(Renderer,0,0,0,0);
    SDL_RenderClear(Renderer);
    container.Render(delta,Renderer);
    SDL_RenderPresent(Renderer);
}

void paraBall::Unload()
{
}