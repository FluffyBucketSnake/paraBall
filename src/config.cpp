#include <config.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

void ConfigTracker::Init(Game *game)
{
    //Set pointer to game instance.
    _game = game;
    //Set default configurations.
    std::cout << "Setting default settings for application." << std::endl;
    SetWindowFlags(DEFAULTWINDOWFLAGS);
    SetResolution(DEFAULTRESOLUTION);
    SetMaxFPS(DEFAULTMAXFPS);
    SetMasterVolume(DEFAULTMASTERVOLUME);
}

void ConfigTracker::LoadConfig(const DataFile &dataFile)
{
    //Copy the config from the file.
    SetWindowFlags(dataFile.LoadedData.WindowFlags);
    SetResolution(dataFile.LoadedData.Resolution);
    SetMaxFPS(dataFile.LoadedData.MaxFps);
    SetMasterVolume(dataFile.LoadedData.MasterVolume);
}

void ConfigTracker::SaveConfig(DataFile &dataFile) const
{
    //Copy the config into the file.
    dataFile.LoadedData.WindowFlags = GetWindowFlags();
    dataFile.LoadedData.Resolution = GetResolution();
    dataFile.LoadedData.MaxFps = GetMaxFPS();
    dataFile.LoadedData.MasterVolume = GetMasterVolume();
    //Save the data into the file.
    dataFile.Save();
}

Uint32 ConfigTracker::GetWindowFlags() const
{
    //Null check.
    if (_game != NULL)
        return _game->GetWindowFlags();
    else
        return 0;
}

void ConfigTracker::SetWindowFlags(Uint32 flags)
{
    //Null check.
    if (_game == NULL)
        return;
    //Make the game define the flags.
    _game->SetWindowFlags(flags);
}

SDL_Point ConfigTracker::GetResolution() const
{
    //Null check.
    if (_game != NULL)
        return _game->GetWindowSize();
    else
        return {-1,-1};
}

void ConfigTracker::SetResolution(SDL_Point resolution)
{
    //Null check.
    if (_game == NULL)
        return;
    //Set the window size.
    _game->SetWindowSize(resolution.x,resolution.y);
}

int ConfigTracker::GetMaxFPS() const
{
    //Null check.
    if (_game != NULL)
        return _game->MaxFPS;
    else
        return -1;
}

void ConfigTracker::SetMaxFPS(int maxFPS)
{
    //Null check.
    if (_game == NULL)
        return;
    //Set the window size.
    _game->MaxFPS = maxFPS;
}

int ConfigTracker::GetMasterVolume() const
{
    //Null check.
    if (_game != NULL)
        return _game->GetMasterVolume();
    else
        return -1;
}

void ConfigTracker::SetMasterVolume(int volume)
{
    //Null check.
    if (_game != NULL)
        return _game->SetMasterVolume(volume);
}