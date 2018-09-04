#include <global.h>

const char* TITLE = "paraBall";
const char* VERSION = "Alpha";

Mix_Chunk* SFX_CURSORMOVE;
Mix_Chunk* SFX_SELECT;
Mix_Chunk* SFX_POINT;
Mix_Chunk* SFX_DEATH;
Mix_Chunk* SFX_COLLISION;

Font* FONT_NORMAL;
Font* FONT_TITLE;

ScreenManager SCREENMANAGER;

int TITLESCREEN;
int LEVELSCREEN;
int GAMEOVERSCREEN;
