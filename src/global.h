#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <graphics/font.h>
#include <screens/screenmanager.h>
#include <data.h>
#include <config.h>

extern const char* TITLE;
extern const char* VERSION;
const int SCREENWIDTH = 320;
const int SCREENHEIGHT = 240;

extern Mix_Chunk* SFX_CURSORMOVE;
extern Mix_Chunk* SFX_SELECT;
extern Mix_Chunk* SFX_COLLISION;
extern Mix_Chunk* SFX_POINT;
extern Mix_Chunk* SFX_DEATH;

extern Font* FONT_NORMAL;
extern Font* FONT_TITLE;

extern DataFile DATAFILE;
extern ScreenManager SCREENMANAGER;
extern ConfigTracker CONFIGTRACKER;

extern int TITLESCREEN;
extern int LEVELSCREEN;
extern int GAMEOVERSCREEN;