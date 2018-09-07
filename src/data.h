#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>

struct Data{
    int WindowFlags = 0;
    SDL_Point Resolution = {320,240};
    int MaxFps = 60;
    int MasterVolume = SDL_MIX_MAXVOLUME;
};

struct DataFile{
    std::fstream Stream;
    Data LoadedData;

    void Open(const std::string &filePath);
    void Load();
    void Save();
    void Close();
};