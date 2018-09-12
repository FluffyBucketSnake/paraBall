#pragma once
#include <screens/screen.h>

class OptionsScreen : public Screen
{
    private:

    public:
        void Init();
        void Unload();
        void Resume();
        void Pause();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};