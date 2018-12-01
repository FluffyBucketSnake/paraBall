#pragma once
#include <screens/screen.h>
#include <paraBall.h>

class TitleScreen : public Screen
{
    private:
        paraBall &_game;
        
        static void Play();
        static void Options();
        static void Exit();
    public:
        TitleScreen(paraBall &game);

        void Init();
        void Unload();
        void Resume();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};