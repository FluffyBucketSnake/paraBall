#include <game.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

bool Game::PreInit()
{
    //Inicializar subsistemas do SDL2.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "[ERROR]SDL_Init: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Criar janela principal.
    Window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 
    SDL_WINDOW_SHOWN);
    if (Window == NULL)
    {
        std::cerr << "[ERROR]SDL_CreateWindow: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    SDL_SetWindowFullscreen(Window,_flags);
    //Criar renderizador.
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == NULL)
    {
        std::cerr << "[ERROR]SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    SDL_SetRenderDrawBlendMode(Renderer,SDL_BLENDMODE_BLEND);
    //Inicializar SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096) != 0)
    {
        std::cerr << "[ERROR]Mix_OpenAudio: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    Mix_Volume(-1,masterVolume);
    //Inicializar TTF.
    if (TTF_Init() != 0)
    {
        std::cerr << "[ERROR]TTF_Init: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Retornar sucesso.
    return true;
}

void Game::HandleEvent(SDL_Event &event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
            //Se a tecla pressionada for ESC, sair do jogo.
            if (event.key.keysym.sym == SDLK_ESCAPE)
                Running = false;
        break;
        case SDL_QUIT:
            //Sair do jogo.
            Running = false;
        break;
    }
}

void Game::Loop()
{
    //Cuidar de todos os eventos recebidos neste ciclo.
    SDL_Event event;
    while(SDL_PollEvent(&event))
        HandleEvent(event);
    //Calculo do tempo.
    currentTime = SDL_GetTicks();
    deltaTime = currentTime - lastTime;
    //Limitar os FPS.
    if (MaxFPS != 0 && deltaTime < 1000/MaxFPS)
    {
        //Nao se passou tempo suficiente.
        SDL_Delay(1000/MaxFPS - deltaTime);
        //Redefinir o tempo.
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
    }
    //Rodar um ciclo logico.
    Update(deltaTime);
    //Rodar um ciclo grafico.
    Render(deltaTime);
    //Guardar o ultimo tempo.
    lastTime = currentTime;
}

void Game::Dispose()
{
    //Desligar fontes.
    TTF_Quit();
    //Desligar audio.
    Mix_CloseAudio();
    //Limpar renderizador.
    if (Renderer != NULL)
        SDL_DestroyRenderer(Renderer);
    //Limpar janela.
    if (Window != NULL)
        SDL_DestroyWindow(Window);
    //Desligar subsistemas.
    SDL_Quit();
}

int Game::Run()
{
    //Chamar a funcao de preinicializacao. Se falhar, retornar -1.
    if (!PreInit())
        return -1;
    //Definir a bandeira de rodar.
    Running = true;
    //Chamar funcao de inicializacao das classes filhas.
    Init();
    //Loopar o jogo enquanto a bandeira 'running' é vetor.
    while(Running)
        Loop();
    //Liberar memoria ocupada.
    Dispose();
    //Retornar codigo de erro 0.
    return 0;
}

const char* Game::GetWindowTitle() const
{
    return title;
}

void Game::SetWindowTitle(const char* newtitle)
{
    //Trocar o ponteiro.
    title = newtitle;
    //Se a janela ja estiver aberta, atualizar o seu titulo.
    if (Window != NULL)
        SDL_SetWindowTitle(Window,title);
}

SDL_Point Game::GetWindowSize() const
{
    return {windowWidth,windowHeight};
}

void Game::SetWindowSize(const int newWidth, const int newHeight)
{
    //Guardar os novos valores.
    windowWidth = newWidth;
    windowHeight = newHeight;
    //Se a janela ja foi criada, redefinir seu tamanho.
    if (Window != NULL)
        SDL_SetWindowSize(Window,windowWidth,windowHeight);
}

Uint32 Game::GetWindowFlags() const
{
    return _flags;
}

void Game::SetWindowFlags(const Uint32 flags)
{
    //Save the newly defined flags.
    _flags = flags;
    //Check if the window already exists, if so, and set their flag.
    if (Window != NULL)
        SDL_SetWindowFullscreen(Window,_flags);
}

int Game::GetMasterVolume() const
{
    return masterVolume;
}

void Game::SetMasterVolume(const int volume)
{
    masterVolume = volume;
    Mix_Volume(-1,volume);
}