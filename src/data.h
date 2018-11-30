#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>

namespace Data
{
    struct Data
    {
        Uint32 Fullscreen;
        int WindowWidth;
        int WindowHeight;
        int MaxFPS;
        
        int MasterVolume;

        int Highscore;
    };

    extern Data _data;

    void Open(const std::string& path);
    void Close();
    void Load();
    void Save();
    bool IsOpen();
    const std::string& GetCurrentPath();

    void Reset();

    void ToggleFullscreen(Uint32 value);
    Uint32 GetFullscreen();
    void SetResolution(int width, int height);
    void GetResolution(int &width, int &height);
    void SetMaxFPS(int value);
    int GetMaxFPS();

    void SetMasterVolume(int value);
    int GetMasterVolume();

    void SetHighscore(int value);
    int GetHighscore();

    extern std::fstream* _stream;
    extern std::string* _path;

    void _assert();
}