#pragma once
#include <screens/screen.h>

class GameOverScreen : public Screen
{
    private:
        const int OPTIONY[2] = {70,58};
        int _current = 0;

        void Restart();
        void GotoTitle();
    public:
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};