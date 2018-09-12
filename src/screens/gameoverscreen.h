#pragma once
#include <screens/screen.h>
#include <interface/menu.h>

class GameOverScreen : public Screen
{
    private:
        const int OPTIONY[2] = {70,58};
        UIMenu menu;

        static void Restart();
        static void GotoTitle();
    public:
        void Init();
        void Unload();
        void Resume();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};