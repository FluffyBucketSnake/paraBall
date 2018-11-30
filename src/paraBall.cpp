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
    //Carregar conteudo.
    Load();
    //Definir semente.
    std::srand(time(nullptr));
    //Criar telas.
    TITLESCREEN = SCREENMANAGER.AddScreen(new TitleScreen(*this),-3,-3,true,true);
    LEVELSCREEN = SCREENMANAGER.AddScreen(new LevelScreen,0,0,false,true);
    GAMEOVERSCREEN = SCREENMANAGER.AddScreen(new GameOverScreen,-1,-1,false,false);
}

void paraBall::Load()
{
    //Iniciar controles.
    Keyboard::Init();
    //Carregar efeitos sonoros.
    SFX_CURSORMOVE = Mix_LoadWAV((std::string(SDL_GetBasePath()) + "sfx/cursormove.wav").c_str());
    if (SFX_CURSORMOVE == nullptr)
    {
        std::cerr << "[ERROR]SFX Loading: " << SDL_GetError() << std::endl;
        Running = false; 
    }
    SFX_SELECT = Mix_LoadWAV((std::string(SDL_GetBasePath()) + "sfx/select.wav").c_str());
    if (SFX_SELECT == nullptr)
    {
        std::cerr << "[ERROR]SFX Loading: " << SDL_GetError() << std::endl;
        Running = false; 
    }
    SFX_COLLISION = Mix_LoadWAV((std::string(SDL_GetBasePath()) + "sfx/collision.wav").c_str());
    if (SFX_COLLISION== nullptr)
    {
        std::cerr << "[ERROR]SFX Loading: " << SDL_GetError() << std::endl;
        Running = false; 
    }
    SFX_DEATH = Mix_LoadWAV((std::string(SDL_GetBasePath()) + "sfx/death.wav").c_str());
    if (SFX_DEATH == nullptr)
    {
        std::cerr << "[ERROR]SFX Loading: " << SDL_GetError() << std::endl;
        Running = false; 
    }
    SFX_POINT = Mix_LoadWAV((std::string(SDL_GetBasePath()) + "sfx/point.wav").c_str());
    if (SFX_POINT == nullptr)
    {
        std::cerr << "[ERROR]SFX Loading: " << SDL_GetError() << std::endl;
        Running = false; 
    }
    //Carregar fontes.
    FONT_NORMAL = Font::LoadFont(Renderer,(std::string(SDL_GetBasePath()) + 
    "/gfx/prstartk.ttf").c_str(),8);
    if (FONT_NORMAL == nullptr)
    {
        std::cerr << "[ERROR]Font Loading: " << SDL_GetError() << std::endl;
        Running = false; 
    }
    FONT_TITLE = Font::LoadFont(Renderer,(std::string(SDL_GetBasePath()) + 
    "/gfx/prstartk.ttf").c_str(),24);
    if (FONT_TITLE == nullptr)
    {
        std::cerr << "[ERROR]Font Loading: " << SDL_GetError() << std::endl;
        Running = false; 
    }
}

void paraBall::Update(int delta)
{
    //Atualizar controles.
    Keyboard::Update();
    //Atualizar telas.
    SCREENMANAGER.Update(delta);
}

void paraBall::Render(int delta)
{   
    //Limpar tela.
    SDL_SetRenderDrawColor(Renderer,0,0,0,0);
    SDL_RenderClear(Renderer);
    //Renderizar telas.
    SCREENMANAGER.Render(Renderer,delta);
    //Presentar resultados.
    SDL_RenderPresent(Renderer);
}

void paraBall::Unload()
{
    //Destruir fase atual.
    SCREENMANAGER.ClearScreens();
    //Liberar efeitos sonoros.
    Mix_FreeChunk(SFX_CURSORMOVE);
    Mix_FreeChunk(SFX_SELECT);
    Mix_FreeChunk(SFX_COLLISION);
    Mix_FreeChunk(SFX_DEATH);
    Mix_FreeChunk(SFX_POINT);
    //Liberar fontes.
    Font::DestroyFont(FONT_NORMAL);
    Font::DestroyFont(FONT_TITLE);
    //Liberar controles.
    Keyboard::Quit();
}