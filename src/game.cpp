#include <game.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

bool Game::PreInit()
{
    //Inicializar subsistemas do SDL2.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "[ERROR]" << "SDL_Init" << ": " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Criar janela principal.
    Window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 
    SDL_WINDOW_SHOWN);
    if (Window == NULL)
    {
        std::cerr << "[ERROR]" << "SDL_CreateWindow" << ": " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Criar renderizador.
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == NULL)
    {
        std::cerr << "[ERROR]" << "SDL_CreateRenderer" << ": " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    SDL_SetRenderDrawBlendMode(Renderer,SDL_BLENDMODE_BLEND);
    //Inicializar SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096) != 0)
    {
        std::cerr << "[ERROR]" << "Mix_OpenAudio" << ": " << SDL_GetError() << std::endl;
        Dispose();
        return false;
    }
    //Inicializar TTF.
    if (TTF_Init() != 0)
    {
        std::cerr << "[ERROR]" << "TTF_Init" << ": " << SDL_GetError() << std::endl;
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
    if (FPS != 0 && deltaTime < 1000/FPS)
    {
        //Nao se passou tempo suficiente.
        SDL_Delay(1000/FPS - deltaTime);
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
    Init();
    //Definir a bandeira de rodar.
    Running = true;
    //Loopar o jogo enquanto a bandeira 'running' é vetor.
    while(Running)
        Loop();
    //Liberar memoria ocupada.
    Dispose();
    //Retornar codigo de erro 0.
    return 0;
}

void Game::SetWindowTitle(const char* newtitle)
{
    //Trocar o ponteiro.
    title = newtitle;
    //Se a janela ja estiver aberta, atualizar o seu titulo.
    if (Window != NULL)
        SDL_SetWindowTitle(Window,title);
}

const char* Game::GetWindowTitle()
{
    return title;
}

SDL_Point Game::GetWindowSize()
{
    return {windowWidth,windowHeight};
}

void Game::SetWindowSize(int newWidth, int newHeight)
{
    //Guardar os novos valores.
    windowWidth = newWidth;
    windowHeight = newHeight;
    //Se a janela ja foi criada, redefinir seu tamanho.
    if (Window != NULL)
        SDL_SetWindowSize(Window,windowWidth,windowHeight);
}