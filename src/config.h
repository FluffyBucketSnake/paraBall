#pragma once
#include <game.h>
#include <data.h>

class ConfigTracker
{
    private:
    Game *_game;
    public:
    const SDL_Point DEFAULTRESOLUTION = {320,240};
    const int DEFAULTMASTERVOLUME = SDL_MIX_MAXVOLUME;
    const int DEFAULTMAXFPS = 60;
    const int DEFAULTWINDOWFLAGS = 0;

    void Init(Game *game);

    void LoadConfig(const DataFile &data);
    void SaveConfig(DataFile &data) const;

    void SetWindowFlags(Uint32 flags);
    Uint32 GetWindowFlags() const;

    void SetResolution(SDL_Point resolution);
    SDL_Point GetResolution() const;

    void SetMaxFPS(int maxFps);
    int GetMaxFPS() const;

    void SetMasterVolume(int volume);
    int GetMasterVolume() const;
};