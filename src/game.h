#pragma once
#include <SDL2/SDL.h>

class Game
{
    private:
        int deltaTime = 0;
        long lastTime = 0;
        long currentTime = 0;

        bool PreInit(); //Carregamento do SDL e seus subsistemas.
        void Loop();    //Responsavel da execucao de cada quadro.
        void HandleEvent(SDL_Event &event); //Controle de eventos do quadro atual.
        void Dispose(); //Libera o conteudo carregado.
    protected:
        SDL_Window* Window = nullptr; //Janela principal da jogo.
        SDL_Renderer* Renderer = nullptr; //Renderizador da janela do jogo.

        virtual void Init() = 0;
        virtual void Update(int delta) = 0;
        virtual void Render(int delta) = 0;
        virtual void Load() = 0;
        virtual void Unload() = 0;
    public:
        bool Running = true;
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