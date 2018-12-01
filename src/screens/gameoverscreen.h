#pragma once
#include <screens/screen.h>

class GameOverScreen : public Screen
{
    private:
        static void Restart();
        static void GotoTitle();
    public:
        void Init();
        void Unload();
        void Resume();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};