#pragma once
#include <SDL2/SDL.h>

class Game
{
    private:
        const char* title = NULL;  //Titulo da janela.
        int windowWidth = 320;
        int windowHeight = 240;
        Uint32 _flags = 0;
        int masterVolume = SDL_MIX_MAXVOLUME;

        int deltaTime = 0;
        long lastTime = 0;
        long currentTime = 0;

        bool PreInit(); //Carregamento do SDL e seus subsistemas.
        void Loop();    //Responsavel da execucao de cada quadro.
        void HandleEvent(SDL_Event &event); //Controle de eventos do quadro atual.
        void Dispose(); //Libera o conteudo carregado.
    protected:
        bool Running;   //Bandeira de execuacao. O jogo fechara quando a bandeira for marcada como falsa.
        SDL_Window* Window = NULL; //Janela principal da jogo.
        SDL_Renderer* Renderer = NULL; //Renderizador da janela do jogo.

        virtual void Init() = 0;
        virtual void Update(int delta) = 0;
        virtual void Render(int delta) = 0;
        virtual void Load() = 0;
        virtual void Unload() = 0;
    public:
        int MaxFPS = 0;

        int Run();
        SDL_Point GetWindowSize() const;
        void SetWindowSize(const int newWidth, const int newHeight);
        Uint32 GetWindowFlags() const;
        void SetWindowFlags(const Uint32 flags);
        const char* GetWindowTitle() const;
        void SetWindowTitle(const char* newtitle);
        int GetMasterVolume() const;
        void SetMasterVolume(const int volume);
};