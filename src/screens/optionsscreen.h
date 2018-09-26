#pragma once
#include <screens/screen.h>
#include <interface/menu.h>


static const SDL_Point RESOLUTIONS[3] = {{320,240},{640,480},{1280,960}};
static const Uint32 WINDOWMODES[3] = {0,SDL_WINDOW_FULLSCREEN_DESKTOP,SDL_WINDOW_FULLSCREEN};
static const int MAXFPS[3] = {0,30,60};

class OptionsScreen : public Screen
{
    private:
        UIMenu menu;

        static int curWndMode;
        static int curResolution;
        static int curMaxFPS;
        static int curMstVol;

        static void Apply();
        static void GoBack();
    public:

        void Init();
        void Unload();
        void Resume();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};