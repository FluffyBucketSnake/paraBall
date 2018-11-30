#include <game.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

bool Game::PreInit()
{
    //Inicializar subsistemas do SDL2.
    std::clog << "[Log]Starting SDL2 subsystems..." << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "[ERROR]SDL_Init: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Criar janela principal.
    std::clog << "[Log]Creating game window..." << std::endl;
    Window = SDL_CreateWindow(nullptr,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 320, 240, 
    SDL_WINDOW_SHOWN);
    if (Window == nullptr)
    {
        std::cerr << "[ERROR]SDL_CreateWindow: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Criar renderizador.
    std::clog << "[Log]Creating renderer..." << std::endl;
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == nullptr)
    {
        std::cerr << "[ERROR]SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    SDL_SetRenderDrawBlendMode(Renderer,SDL_BLENDMODE_BLEND);
    //Inicializar SDL_mixer
    std::clog << "[Log]Initializing SDL2_mixer..." << std::endl;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096) != 0)
    {
        std::cerr << "[ERROR]Mix_OpenAudio: " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Inicializar TTF.
    std::clog << "[Log]Initializing SDL2_ttf..." << std::endl;
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
    if (Renderer != nullptr)
        SDL_DestroyRenderer(Renderer);
    //Limpar janela.
    if (Window != nullptr)
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
    //Loopar o jogo enquanto a bandeira 'running' é verdadeira.
    while(Running)
        Loop();
    //Liberar memoria ocupada.
    Unload();
    Dispose();
    //Retornar codigo de erro 0.
    return 0;
}