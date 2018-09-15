#pragma once
#include <screens/screen.h>
#include <interface/menu.h>

class OptionsScreen : public Screen
{
    private:
        UIMenu menu;

        static void Apply();
        static void GoBack();
    public:
        void Init();
        void Unload();
        void Resume();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};