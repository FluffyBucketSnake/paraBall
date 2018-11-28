#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>

namespace Data
{
    struct Data
    {
        uint8_t Fullscreen;
        uint32_t WindowWidth;
        uint32_t WindowHeight;
        uint8_t FPSCap;
        
        int8_t MasterVolume;

        uint32_t Highscore;
    };

    extern Data _data;

    void Open(const std::string& path);
    void Close();
    void Load();
    void Save();
    bool IsOpen();
    const std::string& GetCurrentPath();

    void Reset();

    void ToggleFullscreen(uint8_t value);
    uint8_t GetFullscreen();
    void SetResolution(uint32_t width, uint32_t height);
    void GetResolution(uint32_t* width, uint32_t* height);
    void SetFPSCap(uint32_t value);
    uint32_t GetFPSCap();

    void SetMasterVolume(int8_t value);
    int8_t GetMasterVolume();

    void SetHighscore(uint32_t value);
    uint32_t GetHighscore();

    extern std::fstream* _stream;
    extern std::string* _path;

    void _assert();
}