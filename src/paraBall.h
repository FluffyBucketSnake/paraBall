#pragma once
#include <game.h>
#include <screens/screen.h>

class paraBall : public Game
{
    public:
        void Init();
        void Update(int delta);
        void Render(int delta);
        void Load();
        void Unload();
};