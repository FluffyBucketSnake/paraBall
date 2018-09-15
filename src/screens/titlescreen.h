#pragma once
#include <screens/screen.h>
#include <interface/menu.h>
#include <paraBall.h>

class TitleScreen : public Screen
{
    private:
        UIMenu menu;
        paraBall *_game;
        
        static void Play();
        static void Options();
        static void Exit();
    public:
        void Init();
        void Unload();
        void Resume();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};